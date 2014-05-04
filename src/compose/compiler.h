//------------------------------------------------------------------------------
// compiler.h - Compose script compiler
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

#ifndef GAEN_COMPOSE_COMPILER_H
#define GAEN_COMPOSE_COMPILER_H

#include "core/base_defines.h"
#include "compose/compiler_utils.h"

extern "C" {
#include "compose/parser.h"
}

typedef enum yytokentype TokenType;

struct ast_node{};
struct sym_record {};
struct sym_table {};

namespace gaen
{

// C++ Declarations

class AstNode : public ast_node
{
public:
    static AstNode * convert(ast_node * pAstNode) { return static_cast<AstNode*>(pAstNode); }

    AstNode(TokenType tokenType) {};
};

class SymRecord : public sym_record
{
public:
    static SymRecord * convert(sym_record * pSymRec) { return static_cast<SymRecord*>(pSymRec); }

    SymRecord(const char * name);
};


class SymTable : public sym_table
{
public:
    static SymTable * convert(sym_table * pSymTab) { return static_cast<SymTable*>(pSymTab); }


    void pushScope();
    void popScope();
    void addEntry(SymRecord * pSymRecord);
};


class Program
{
public:
    Program(AstNode * pRoot, SymTable * pSymTable);
    ~Program();

    const AstNode & rootNode() { return *mpRoot; }
    const SymTable & symTable() { return *mpSymTable; }

private:
    AstNode  * mpRoot;
    SymTable * mpSymTable;
};

Program * compile(const u8 * source, size_t length);


}



#endif
