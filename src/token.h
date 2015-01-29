#pragma once
#include "tokenType.h"

/**
* Class for token container. Use token type to fill it symbol and instruction.
*/
class CToken {
	private:
		int id;
		std::string value;
		TokenSymbol::Symbol symbol;
		TokenInstruction::Instruction kind;
	public:
		CToken(int id, std::string value, TokenSymbol::Symbol symbol, TokenInstruction::Instruction kind):id(id),value(value),symbol(symbol),kind(kind){};
		int getId(){return id;};
		std::string getValue(){return value;};
		TokenSymbol::Symbol getSymbol(){return symbol;};
		TokenInstruction::Instruction getKind(){return kind;};
};
