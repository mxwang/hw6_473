#include "llvm/Analysis/Passes.h"
#include "llvm/IR/Verifier.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
//#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Bitcode/ReaderWriter.h"
#include <cstdio>
#include <map>
#include <string>
#include <vector>
namespace project473 {
extern "C" {
  #include "ast.h"
}
}

using namespace llvm;

extern "C" int initLex(int argc, char** argv);
extern "C" void initSymbolTable();  
extern "C" int  yyparse();
extern "C" int typecheck();
extern "C" int gettoken();
extern "C" void print_Ast();
extern "C" void printSymbolTable(int flag); 
extern "C" project473::AstNodePtr program;
extern "C" project473::SymbolTableStackEntryPtr symbolStackTop;

static Module *TheModule;
static IRBuilder<> Builder(getGlobalContext());
static std::map<std::string, AllocaInst*> NamedValues;
static std::map<std::string, Function*> Functions;
BasicBlock *ReturnBB=0;
AllocaInst *RetAlloca=0;
void Error(const char *Str) { fprintf(stderr, "Error: %s\n", Str);}
Value *ErrorV(const char *Str) { Error(Str); return 0; }

/// CreateEntryBlockAlloca - Create an alloca instruction in the entry block of
/// the function.  VarName is an std::string containing the variable name
static AllocaInst *CreateEntryBlockAlloca(Function *TheFunction, const std::string &VarName) {
  
}

/// CreateEntryBlockArrayAlloca - Create an alloca instruction for an array in the entry block of
/// the function.  VarName is an std::string containing the array name, arraySize is the number of elements in the array
static AllocaInst *CreateEntryBlockArrayAlloca(Function *TheFunction, const std::string &VarName, int arraySize) {

}

///Codegen the Allocas for local variables that correspond to the formal variables of function F.
///function_node is an AST node representing a function. Steps
///1. For every formal variable, get its name from the AST, create a Type object
// and call AllocaInst* alloca_inst = Builder.CreateAlloca(Type, name);
//2. set NamedValues[name] = alloca_inst
//3. For every formal variable of the function, create a store instruction that copies the value
//from the formal variable to the allocated local variable.
void createFormalVarAllocations(Function *F, project473::AstNodePtr function_node) {

}

Function* Codegen_Function_Declaration(project473::AstNodePtr declaration_node) {
  char* fname = strdup(declaration_node->nSymbolPtr->id); 
  std::string Name(fname);
  std::vector<Type*> formalvars;
  project473::AstNodePtr formalVar = declaration_node->children[0]; 
  while(formalVar) { 
    if(formalVar->nSymbolPtr->stype->kind == project473::INT) {
      formalvars.push_back(Type::getInt32Ty(getGlobalContext()));
      formalVar=formalVar->sibling;
    }
    else {
      printf("Error, formal variable is not an int, in line: %d", formalVar->nLinenumber);
    }
  }
  project473::Type* functionTypeList = declaration_node->nSymbolPtr->stype->function;
  FunctionType *FT;
  if(functionTypeList->kind==project473::INT) { 
     FT = FunctionType::get(Type::getInt32Ty(getGlobalContext()), formalvars, false);
  }
  else if(functionTypeList->kind==project473::VOID) {
    FT = FunctionType::get(Type::getVoidTy(getGlobalContext()), formalvars, false);
  }

  Function *F = Function::Create(FT, Function::ExternalLinkage, Name, TheModule);
  // Set names for all arguments. Reuse formalVar
  formalVar = declaration_node->children[0];
  for (Function::arg_iterator AI = F->arg_begin(); formalVar != NULL; ++AI, formalVar=formalVar->sibling) {
          std::string argName(formalVar->nSymbolPtr->id);
          AI->setName(argName);
  }
  Functions[Name] = F; //add the Function to the map of functions
  return F;
}

///Generate code for expressions
Value* Codegen_Expression(project473::AstNodePtr expression) {
    if(expression->eKind==project473::ASSI_EXP) {
      
    }
    else if(expression->eKind==project473::VAR_EXP) {
        
    }
    else if(expression->eKind==project473::CONST_EXP) {
      
    }
    else if(expression->eKind==project473::GT_EXP) {
        
    }
    else if(expression->eKind==project473::LT_EXP) {
       
    }
    else if(expression->eKind==project473::GE_EXP) {
       
    }
    else if(expression->eKind==project473::LE_EXP) {
        
    }
    else if(expression->eKind==project473::EQ_EXP) {
       
    }
    else if(expression->eKind==project473::NE_EXP) {
       
    }
    else if(expression->eKind==project473::ADD_EXP) {
       
    }
    else if(expression->eKind==project473::SUB_EXP) {
        
    }
    else if(expression->eKind==project473::MULT_EXP) {
        
    }
    else if(expression->eKind==project473::DIV_EXP) {
        
    }
    else if(expression->eKind==project473::ARRAY_EXP) {
        
    }
    else if(expression->eKind==project473::CALL_EXP) { 
       
    }
  return 0;
}

///Generates code for the statements.
//Calls Codegen_Expression
Value* Codegen_Statement(project473::AstNodePtr statement) {
    if(statement->sKind==project473::EXPRESSION_STMT) {
          
    }
    else if(statement->sKind==project473::RETURN_STMT) {
          
    }
    else if(statement->sKind==project473::IF_THEN_ELSE_STMT) { 

    }
    else if(statement->sKind==project473::COMPOUND_STMT) {
         
    }
    else if(statement->sKind==project473::WHILE_STMT) {
          
    }
    return 0; 

}

//generates the code for the body of the function. Steps
//1. Generate alloca instructions for the local variables
//2. Iterate over list of statements and call Codegen_Statement for each of them
Value* Codegen_Function_Body(project473::AstNodePtr function_body) {
   
}

//generates code for the function, verifies the code for the function. Steps:
//1. Create the entry block, place the insert point for the builder in the entry block
//2. Call CreateFormalVarAllocations
//3. Call Codegen_Function_Body
//4. Insert 'return' basic block if needed
Function* Codegen_Function(project473::AstNodePtr function_node) {

}

void initializeFunctions(project473::AstNodePtr program) {
    project473::AstNodePtr currentFun = program;
    while(currentFun != NULL) {
       Function *TheFunction = Codegen_Function_Declaration(currentFun);
       currentFun=currentFun->sibling;
    }
}

void codegen() {
  InitializeNativeTarget();
  LLVMContext &Context = getGlobalContext();
  // Make the module, which holds all the code.
  TheModule = new Module("filename", Context);
  //Codegen the global variables
  project473::ElementPtr currentGlobal = symbolStackTop->symbolTablePtr->queue;
  while(currentGlobal != NULL) {
    if (currentGlobal->stype->kind==project473::INT) {
	/*Code here*/
    }
    else if(currentGlobal->stype->kind==project473::ARRAY) {
	/*Code here*/
    }
    currentGlobal = currentGlobal->queue_next;
  }
  
  initializeFunctions(program);
  project473::AstNodePtr currentFunction = program;
  while(currentFunction != NULL) {
    Function* theFunction = Codegen_Function(currentFunction); 
    currentFunction = currentFunction->sibling; 
  }
  // Print out all of the generated code.
  std::error_code ErrInfo;
  llvm::raw_ostream* filestream = new llvm::raw_fd_ostream("/home/rigel/hw6/out.s",ErrInfo, llvm::sys::fs::F_None);
  TheModule->print(*filestream,0);
}

int main(int argc, char** argv) {
  initLex(argc,argv);
    initSymbolTable();  
    yyparse();
    int typ = typecheck();
    printf("\ntypecheck returned: %d\n", typ);
    codegen();
 return 0;
}
