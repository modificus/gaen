//------------------------------------------------------------------------------
// codegen_cpp.cpp - C++ code generation
//
// Gaen Concurrency Engine - http://gaen.org
// Copyright (c) 2014 Lachlan Orr
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//   1. The origin of this software must not be misrepresented; you must not
//   claim that you wrote the original software. If you use this software
//   in a product, an acknowledgment in the product documentation would be
//   appreciated but is not required.
//
//   2. Altered source versions must be plainly marked as such, and must not be
//   misrepresented as being the original software.
//
//   3. This notice may not be removed or altered from any source
//   distribution.
//------------------------------------------------------------------------------


#include "engine/hashes.h"
#include "compose/codegen_cpp.h"
#include "compose/compiler_structs.h"
#include "compose/codegen_utils.h"

#include "core/List.h"

namespace gaen
{

#define S String<kMEM_Compose>
#define LF S("\n")
#define I indent(indentLevel)

static S indent(u32 level);
static S type_str(DataType dt);
static S property_block_accessor(const Ast * pAst);
static S binary_op(const Ast * pAst, const char * op);
static S unary_op(const Ast * pAst, const char* op);
static S unary_op_post(const Ast * pAst, const char* op);
static S assign(const Ast * pAst, const char * op);

static S message_id(const Ast *pMsgSend);

static S symref(const SymRec * pSymRec);

static S codegen_recurse(const Ast * pAst,
                         int indentLevel);

static S indent(u32 level)
{
    static const char * sIndents[] = { "",
                                       "    ",
                                       "        ",
                                       "            ",
                                       "                ",
                                       "                    ",
                                       "                        ",
                                       "                            "};
    static const u32 kMaxLevel = sizeof(sIndents) / sizeof(char*);

    if (level >= kMaxLevel)
        level = kMaxLevel - 1;

    return S(sIndents[level]);
}

static S type_str(DataType dt)
{
    switch (dt)
    {
    case kDT_int:
        return S("int");
    case kDT_uint:
        return S("uint");
    case kDT_float:
        return S("float");
    case kDT_bool:
        return S("bool");
    case kDT_char:
        return S("char");
    case kDT_vec3:
        return S("Vec3");
    case kDT_vec4:
        return S("Vec4");
    case kDT_mat3:
        return S("Mat3");
    case kDT_mat34:
        return S("Mat34");
    case kDT_mat4:
        return S("Mat4");
    case kDT_void:
        return S("void");
    default:
        PANIC("type_str invalid DataType: %d", dt);
        return S("");
    }
}

static S property_block_accessor(const Ast * pAst)
{
    ASSERT(pAst && pAst->pSymRec);
    
    static const u32 kScratchSize = 255;
    char scratch[kScratchSize+1];
    scratch[kScratchSize] = '\0';
        
    switch (pAst->pSymRec->dataType)
    {
    case kDT_int:
        snprintf(scratch, kScratchSize, "mpBlocks[%u].cells[%u].i", pAst->pSymRec->blockIndex, pAst->pSymRec->cellIndex);
        return S(scratch);
    case kDT_uint:
        snprintf(scratch, kScratchSize, "mpBlocks[%u].cells[%u].u", pAst->pSymRec->blockIndex, pAst->pSymRec->cellIndex);
        return S(scratch);
    case kDT_float:
        snprintf(scratch, kScratchSize, "mpBlocks[%u].cells[%u].f", pAst->pSymRec->blockIndex, pAst->pSymRec->cellIndex);
        return S(scratch);
    case kDT_bool:
        snprintf(scratch, kScratchSize, "mpBlocks[%u].cells[%u].b", pAst->pSymRec->blockIndex, pAst->pSymRec->cellIndex);
        return S(scratch);
    case kDT_char:
        snprintf(scratch, kScratchSize, "mpBlocks[%u].cells[%u].c", pAst->pSymRec->blockIndex, pAst->pSymRec->cellIndex);
        return S(scratch);
    case kDT_color:
        snprintf(scratch, kScratchSize, "mpBlocks[%u].cells[%u].color", pAst->pSymRec->blockIndex, pAst->pSymRec->cellIndex);
        return S(scratch);
    case kDT_vec3:
        ASSERT(pAst->pSymRec->cellIndex == 0);
        snprintf(scratch, kScratchSize, "*static_cast<Vec3*>(&mpBlocks[%u].qCell)", pAst->pSymRec->blockIndex);
        return S(scratch);
    case kDT_vec4:
        ASSERT(pAst->pSymRec->cellIndex == 0);
        snprintf(scratch, kScratchSize, "*static_cast<Vec4*>(&mpBlocks[%u].qCell)", pAst->pSymRec->blockIndex);
        return S(scratch);
    case kDT_mat3:
        ASSERT(pAst->pSymRec->cellIndex == 0);
        snprintf(scratch, kScratchSize, "*static_cast<Mat3*>(&mpBlocks[%u].qCell)", pAst->pSymRec->blockIndex);
        return S(scratch);
    case kDT_mat34:
        ASSERT(pAst->pSymRec->cellIndex == 0);
        snprintf(scratch, kScratchSize, "*static_cast<Mat34*>(&mpBlocks[%u].qCell)", pAst->pSymRec->blockIndex);
        return S(scratch);
    case kDT_mat4:
        ASSERT(pAst->pSymRec->cellIndex == 0);
        snprintf(scratch, kScratchSize, "*static_cast<Mat4*>(&mpBlocks[%u].qCell)", pAst->pSymRec->blockIndex);
        return S(scratch);
    default:
        PANIC("Invalid dataType: %d", pAst->pSymRec->dataType);
        return S("");
    }
}


static S binary_op(const Ast * pAst, const char * op)
{
    return S("(") + codegen_recurse(pAst->pLhs, 0) + S(" ") + S(op) + S(" ") + codegen_recurse(pAst->pRhs, 0) + S(")");
}

static S unary_op(const Ast * pAst, const char* op)
{
    return S(op) + S("(") + codegen_recurse(pAst->pRhs, 0) + S(")");
}

static S unary_op_post(const Ast * pAst, const char* op)
{
    return S("(") + codegen_recurse(pAst->pRhs, 0) + S(")") + S(op);
}

static S assign(const Ast * pAst, const char * op)
{
    return symref(pAst->pSymRec) + S(" ") + S(op) + S(" ") + codegen_recurse(pAst->pRhs, 0);
}

static S message_id(const Ast *pMsgSend)
{

}

static S symref(const SymRec * pSymRec)
{
    ASSERT(pSymRec);

    S code(pSymRec->name);

    if (is_prop_or_field(pSymRec))
    {
        code += S("()"); // properties and fields are accessed from mpBlocks using generated private accessors
    }
    return code;
}

static S codegen_recurse(const Ast * pAst,
                         int indentLevel)
{
    ASSERT(pAst);

    switch (pAst->type)
    {
    case kAST_FunctionDef:
    {
        return S("");
    }
    case kAST_EntityDef:
    {
        const Ast * pUpdateDef = find_update_message_def(pAst);
        S entName = S(pAst->pSymRec->name);

        S code("namespace ent\n{\n\n");
        code += I + S("class ") + entName + S(" : public Entity\n{\n");

        code += I + S("public:\n");
        code += I + S("    static Entity * construct(u32 childCount)\n");
        code += I + S("    {\n");
        code += I + S("        return GNEW(kMEM_Engine, ") + entName + S(", childCount);\n");
        code += I + S("    }\n");
        code += I + S("    \n");

        // Update method, if we have one
        if (pUpdateDef)
        {
            code += codegen_recurse(pUpdateDef, indentLevel + 1);
            code += I + S("\n");
        }

        // LORRTEMP - these are here just to get things to compile, replace with proper codegenerated ones
        code += I + S("    template <typename T>\n");
        code += I + S("    MessageResult message(const T & msgAcc) { return MessageResult::Propogate; }\n");
        code += I + S("\n");

        code += I + S("private:\n");

        // Constructor
        code += I + S("    ") + entName + S("(u32 childCount)\n");
        code += I + S("      : Entity(HASH::") + entName + S(", childCount, 36, 36)\n");
        code += I + S("    {\n");
        // Initialize fields and properties
        for (const auto & kv : pAst->pScope->pSymTab->dict)
        {
            if (is_prop_or_field(kv.second))
            {
                code += I + S("        ") + symref(kv.second) + S(" = ");
                ASSERT(kv.second->pAst);
                code += codegen_recurse(kv.second->pAst, 0);
                code += S(";\n");
            }
        }
        code += I + S("    }\n");

        // Delete copy constructor, assignment, etc.
        code += I + S("    ") + entName + S("(const ") + entName + S("&)              = delete;\n");
        code += I + S("    ") + entName + S("(const ") + entName + S("&&)             = delete;\n");
        code += I + S("    ") + entName + S(" & operator=(const ") + entName + S("&)  = delete;\n");
        code += I + S("    ") + entName + S(" & operator=(const ") + entName + S("&&) = delete;\n");

        code += S("\n");

        // Property and fields accessors into mpBlocks
        for (Ast * pChild : pAst->pChildren->nodes)
        {
            if (is_prop_or_field(pChild->pSymRec))
            {
                code += codegen_recurse(pChild, indentLevel + 1);
            }
        }

        code += S("\n");
        
        // mBlocks, the only data member, all data is stored in 16 byte blocks
        {
            static const u32 kScratchSize = 32;
            char scratch[kScratchSize+1];
            scratch[kScratchSize] = '\0'; // sanity null terminator

            snprintf(scratch, kScratchSize, "%d", pAst->pScope->pSymTab->blockCount);
            code += I + S("    Block mBlocks[") + S(scratch) + S("];\n");
        }
        
        code += I + S("};\n\n");

        code += I + S("namespace\n");
        code += I + S("{\n");
        code += (I + S("bool isRegistered = EntityRegistry::register_constructor(HASH::") +
                 entName + S(", ") + entName + S("::construct);\n"));
        code += I + S("}\n");
        code += I + S("\n} // namespace ent\n ");

        return code;
    }
    case kAST_ComponentDef:
    {
        const Ast * pUpdateDef = find_update_message_def(pAst);
        S compName = S(pAst->pSymRec->name);

        S code("namespace comp\n{\n\n");
        code += I + S("class ") + compName + S(" : public Component\n{\n");
        
        code += I + S("public:\n");
        code += I + S("    static Component * construct(void * place)\n");
        code += I + S("    {\n");
        code += I + S("        return new (place) ") + compName + S("();\n");
        code += I + S("    }\n");
        code += I + S("    \n");

        // Update method, if we have one
        if (pUpdateDef)
        {
            code += codegen_recurse(pUpdateDef, indentLevel + 1);
            code += I + S("\n");
        }
        
        // LORRTEMP - these are here just to get things to compile, replace with proper codegenerated ones
        code += I + S("    template <typename T>\n");
        code += I + S("    MessageResult message(const T & msgAcc) { return MessageResult::Propogate; }\n");
        code += I + S("\n");

        code += I + S("private:\n");

        // Constructor
        code += I + S("    ") + compName + S("()\n");
        code += I + S("    {\n");
        // Initialize fields and properties
        for (const auto & kv : pAst->pScope->pSymTab->dict)
        {
            if (is_prop_or_field(kv.second))
            {
                code += I + S("        ") + symref(kv.second) + S(" = ");
                ASSERT(kv.second->pAst);
                code += codegen_recurse(kv.second->pAst, 0);
                code += S(";\n");
            }
        }
        code += S("\n");
        // Create task
        if (pUpdateDef)
        {
            code += I + S("        mTask = Task::createUpdatable(this, HASH::") + compName + S(");\n");
        }
        else
        {
            code += I + S("        mTask = Task::create(this, HASH::") + compName + S(");\n");
        }
        {
            static const u32 kScratchSize = 32;
            char scratch[kScratchSize+1];
            scratch[kScratchSize] = '\0'; // sanity null terminator

            snprintf(scratch, kScratchSize, "%d", pAst->pScope->pSymTab->blockCount);
            code += I + S("        mBlockCount = ") + S(scratch) + S(";\n");
        }

        code += I + S("    }\n");

        // Delete copy constructor, assignment, etc.
        code += I + S("    ") + compName + S("(const ") + compName + S("&)              = delete;\n");
        code += I + S("    ") + compName + S("(const ") + compName + S("&&)             = delete;\n");
        code += I + S("    ") + compName + S(" & operator=(const ") + compName + S("&)  = delete;\n");
        code += I + S("    ") + compName + S(" & operator=(const ") + compName + S("&&) = delete;\n");

        code += S("\n");

        // Property and fields accessors into mBlocks
        for (Ast * pChild : pAst->pChildren->nodes)
        {
            if (is_prop_or_field(pChild->pSymRec))
            {
                code += codegen_recurse(pChild, indentLevel + 1);
            }
        }

        code += S("\n");
        
        code += I + S("};\n\n");

        code += I + S("namespace\n");
        code += I + S("{\n");
        code += (I + S("bool isRegistered = ComponentRegistry::register_constructor(HASH::") +
                 compName + S(", ") + compName + S("::construct);\n"));
        code += I + S("}\n");
        
        code += I + S("\n} // namespace comp\n ");
        return code;
   }
    case kAST_MessageDef:
    {
        S msgName = S(pAst->pSymRec->name);
        S code;
        
        if (is_update_message_def(pAst))
        {
            code += I + S("void update(float deltaSecs)\n");
            code += I + S("{\n");
            for (Ast * pChild : pAst->pChildren->nodes)
            {
                code += codegen_recurse(pChild, indentLevel + 1);
            }
            code += I + S("}\n");
        }
        return code;
    }
    case kAST_PropertyDef:
    case kAST_FieldDef:
    {
        S propName = S(pAst->pSymRec->name);

        S code = I + type_str(pAst->pSymRec->dataType) + S("& ") + propName + S("()\n");
        code += I + S("{\n");
        code += I + S("    return ") + property_block_accessor(pAst) + S(";\n");
        code += I + S("}\n");

        return code;
    }

    case kAST_Block:
    {
        ASSERT(indentLevel > 0);
        S code = indent(indentLevel-1) + S("{\n");
        for (Ast * pChild : pAst->pChildren->nodes)
        {
            code += codegen_recurse(pChild, indentLevel);
        }
        code += indent(indentLevel-1) + S("}\n");
        return code;
    }
//    case kAST_FunctionParams:
//    {
//        return S("");
//    }
    case kAST_FunctionCall:
    {
        return S("");
    }
    case kAST_SymbolRef:
    {
        return symref(pAst->pSymRec);
    }
    case kAST_SymbolDecl:
    {
        return S("");
    }

    case kAST_SimpleStmt:
    {
        return I + codegen_recurse(pAst->pLhs, 0) + S(";\n");
    }

    case kAST_If:
    {
        S code = I + S("if (") + codegen_recurse(pAst->pLhs, 0) + S(")\n");
        code += codegen_recurse(pAst->pMid, indentLevel + 1);
        if (pAst->pRhs)
        {
            code += I + S("else\n");
            code += codegen_recurse(pAst->pRhs, indentLevel + 1);
        }

        return code;
    }
    case kAST_While:
    {
        return S("");
    }
    case kAST_DoWhile:
    {
        return S("");
    }
    case kAST_For:
    {
        return S("");
    }
    
    case kAST_Add:
    {
        return binary_op(pAst, "+");
    }
    case kAST_Sub:
    {
        return binary_op(pAst, "-");
    }
    case kAST_Mul:
    {
        return binary_op(pAst, "*");
    }
    case kAST_Div:
    {
        return binary_op(pAst, "/");
    }
    case kAST_Mod:
    {
        return binary_op(pAst, "%");
    }
    case kAST_LShift:
    {
        return binary_op(pAst, "<<");
    }
    case kAST_RShift:
    {
        return binary_op(pAst, ">>");
    }
    case kAST_And:
    {
        return binary_op(pAst, "&&");
    }
    case kAST_Or:
    {
        return binary_op(pAst, "||");
    }
    case kAST_BitOr:
    {
        return binary_op(pAst, "|");
    }
    case kAST_BitXor:
    {
        return binary_op(pAst, "^");
    }
    case kAST_BitAnd:
    {
        return binary_op(pAst, "&");
    }

    case kAST_Eq:
    {
        return binary_op(pAst, "==");
    }
    case kAST_NEq:
    {
        return binary_op(pAst, "!=");
    }
    case kAST_LT:
    {
        return binary_op(pAst, "<");
    }
    case kAST_LTE:
    {
        return binary_op(pAst, "<=");
    }
    case kAST_GT:
    {
        return binary_op(pAst, ">");
    }
    case kAST_GTE:
    {
        return binary_op(pAst, ">=");
    }

    case kAST_Assign:
    {
        return assign(pAst, "=");
    }
    case kAST_AddAssign:
    {
        return assign(pAst, "+=");
    }
    case kAST_SubAssign:
    {
        return assign(pAst, "-=");
    }
    case kAST_MulAssign:
    {
        return assign(pAst, "*=");
    }
    case kAST_DivAssign:
    {
        return assign(pAst, "/=");
    }
    case kAST_ModAssign:
    {
        return assign(pAst, "%=");
    }
    case kAST_LShiftAssign:
    {
        return assign(pAst, "<<=");
    }
    case kAST_RShiftAssign:
    {
        return assign(pAst, ">>=");
    }
    case kAST_AndAssign:
    {
        return assign(pAst, "&=");
    }
    case kAST_XorAssign:
    {
        return assign(pAst, "^=");
    }
    case kAST_OrAssign:
    {
        return assign(pAst, "|=");
    }

    case kAST_Not:
    {
        return unary_op(pAst, "!");
    }
    case kAST_Complement:
    {
        return unary_op(pAst, "~");
    }
    case kAST_Negate:
    {
        return unary_op(pAst, "-");
    }

    case kAST_PreInc:
    {
        return unary_op(pAst, "++");
    }
    case kAST_PreDec:
    {
        return unary_op(pAst, "--");
    }
    case kAST_PostInc:
    {
        return unary_op_post(pAst->pRhs, "++");
    }
    case kAST_PostDec:
    {
        return unary_op_post(pAst->pRhs, "--");
    }

    case kAST_IntLiteral:
    {
        static const u32 kScratchSize = 64;
        char scratch[kScratchSize+1];
        scratch[kScratchSize] = '\0'; // sanity null terminator
        snprintf(scratch, kScratchSize, "%d", pAst->numi);
        return S(scratch);
    }
    case kAST_FloatLiteral:
    {
        static const u32 kScratchSize = 64;
        char scratch[kScratchSize+1];
        scratch[kScratchSize] = '\0'; // sanity null terminator
        snprintf(scratch, kScratchSize, "%ff", pAst->numf);
        return S(scratch);
    }
    case kAST_StringLiteral:
    {
        return S("");
    }

//    case kAST_Identifier:
//    {
//    }

    case kAST_PropertySet:
    {
        return S("");
    }
    case kAST_MessageSend:
    {
        static const u32 kScratchSize = 255;
        S code;
        code += I + S("{\n");
        S target;
        if (!pAst->pLhs)
            target = S("mpCompDesc->entityTaskId");
        else
            PANIC("Specific target not implemented yet");
        if (pAst->pMid)
            PANIC("Specific component not implemented yet");
        
        char scratch[kScratchSize+1];
        snprintf(scratch,
                 kScratchSize,
                 "MessageBlockWriter msgw(%u, 0, ",
                 HASH::hash_func(pAst->str));

        code += S(scratch);

        if (pAst->pLhs == 0)
            code += S("mEntityTaskId");
        else
            PANIC("TODO");

        code += S(", 0, 0, 0);\n");

        code += I + S("}\n");
        return code;
    }

    default:
        PANIC("codegen_recurse invalid AstType: %d", pAst->type);
        return S("");
    }
}

static void extract_filenames(const S & cmpFullPath,
                              CodeCpp & codeCpp)
{
    codeCpp.cmpFullPath = cmpFullPath;

    if (cmpFullPath.substr(cmpFullPath.size() - 4) != S(".cmp"))
        PANIC("Compose filename doesn't have .cmp extension: %s", cmpFullPath.c_str());

    S scriptsCompose("/scripts/cmp/");

    size_t scriptsComposePos = cmpFullPath.rfind(scriptsCompose);
    if (scriptsComposePos == S::npos)
        PANIC("Compose filename doesn't contain .../scripts/cmp/... directory: %s", cmpFullPath.c_str());

    size_t lastSlashPos = cmpFullPath.rfind('/');

    S relPath = cmpFullPath.substr(scriptsComposePos + scriptsCompose.size(), lastSlashPos - (scriptsComposePos + scriptsCompose.size()) + 1);

    codeCpp.cmpFilename = cmpFullPath.substr(cmpFullPath.rfind('/') + 1);
    // already ends with .cmp
    codeCpp.cppFilename = codeCpp.cmpFilename;
    codeCpp.cppFilename[codeCpp.cppFilename.size() - 2] = 'p';
    codeCpp.cppFilename[codeCpp.cppFilename.size() - 1] = 'p';

    codeCpp.cmpRelPath = relPath + codeCpp.cmpFilename;
    codeCpp.cppRelPath = relPath + codeCpp.cppFilename;
    
    codeCpp.cppFullPath = cmpFullPath.substr(0, scriptsComposePos);
    codeCpp.cppFullPath += "/scripts/cpp/";
    codeCpp.cppFullPath += codeCpp.cppRelPath;
}
                       

CodeCpp codegen_cpp(const ParseData * pParseData)
{
    ASSERT(pParseData);

    CodeCpp codeCpp;

    extract_filenames(pParseData->fullPath, codeCpp);
    
    codeCpp.code = S("");

    codeCpp.code += S("#include \"engine/hashes.h\"\n");
    codeCpp.code += S("#include \"engine/Block.h\"\n");
    codeCpp.code += S("#include \"engine/MessageWriter.h\"\n");
    codeCpp.code += S("#include \"engine/Task.h\"\n");
    codeCpp.code += S("#include \"engine/Registry.h\"\n");
    codeCpp.code += S("#include \"engine/Component.h\"\n");
    codeCpp.code += S("#include \"engine/Entity.h\"\n");
    codeCpp.code += LF;

    codeCpp.code += S("namespace gaen\n{\n\n");

    auto codeDefs = S("");
    for (Ast * pAst : pParseData->pRootAst->pChildren->nodes)
    {
        // only process top level AST nodes from the primary file
        if (pAst->fullPath == pParseData->fullPath)
        {
            codeDefs += codegen_recurse(pAst, 0) + S("\n");
        }
    }

    codeCpp.code += codeDefs;

    codeCpp.code += S("} // namespace gaen\n");

    return codeCpp;
}

} // namespace gaen
