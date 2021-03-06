#include "Lex.h"
#include<list>
#include "WeakScriptLex.h"
SymbolTable st;
class Parser;
enum ErrorCode{
	Err_
};


class ErrorHandler{
	Lex &lex;
	Parser &parser;
public:
	ErrorHandler(Lex &a, Parser &b)
		:lex(a), parser(b){}
	void ThrowError(int code, int line,string info=""){

	}
	void LexLevelErrorRecover(){

	}
}errHandler;
class Parser{
private:
	Lex &lex;
	class Node{
	public:
		virtual void visit(int x) = 0;
		virtual void del() = 0;
	};

	class BinNode : public Node{
		Node *left, *right;
	public:
		BinNode(Node *_l, Node *_r)
			:left(_l), right(_r){
			if (_l == 0 || _r == 0){
				cout << "fuck" << endl;
			}
		}
		void visitson(int x){
			left->visit(x);
			right->visit(x);
		}
		virtual void del(){
			left->del();
			right->del();
			delete left;
			delete right;
		}
	};

	class AddNode :public BinNode{
	public:
		AddNode(Node *_l, Node *_r)
			:BinNode(_l, _r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "AddNode " << endl;
			this->visitson(x + 1);
		}
	};
	class SubNode :public BinNode{
	public:
		SubNode(Node *_l, Node *_r)
			:BinNode(_l, _r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "SubNode " << endl;
			this->visitson(x + 1);
		}
	};
	class MulNode :public BinNode{
	public:
		MulNode(Node *_l, Node *_r)
			:BinNode(_l, _r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "MulNode " << endl;
			this->visitson(x + 1);
		}
	};
	class DivNode :public BinNode{
	public:
		DivNode(Node *_l, Node *_r)
			:BinNode(_l, _r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "DivNode " << endl;
			this->visitson(x + 1);
		}
	};
	class ModNode :public BinNode{
	public:
		ModNode(Node *_l, Node *_r)
			:BinNode(_l, _r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "ModNode " << endl;
			this->visitson(x + 1);
		}
	};
	class StrNode : public Node{
		string code;
	public:
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "StrNode :" << code << endl;
		}
		virtual void del(){

		}
		StrNode(Token x){
			code = x.name;
		}
	};
	class NumNode : public Node{
		string code;
	public:
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "NumNode :" << code << endl;
		}
		virtual void del(){

		}
		NumNode(Token x){
			code = x.name;
		}
	};
	class IdNode :public Node {
		int code;
	public:
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "IdNode :" << code << endl;
		}
		virtual void del(){

		}
		IdNode(Token x){
			code = st.AcceptId(x.name);
		}
	};
	class IdDecNode :public Node {
		int code;
	public:
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "IdDecNode :" << code << endl;
		}
		virtual void del(){

		}
		IdDecNode(Token x){
			code = st.AcceptId(x.name);
		}
	};
	class EmptyNode :public Node{
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "Empty Node" << endl;
		}
		virtual void del(){

		}
	};
	class BreakNode :public Node{
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "Break Node" << endl;
		}
		virtual void del(){

		}
	};
	class ContinueNode :public Node{
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "Continue Node" << endl;
		}
		virtual void del(){

		}
	};
	class RetrunNode :public Node{
		//unfinished
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "Retrun Node" << endl;
		}
		virtual void del(){

		}
	};
	class NegaNode :public Node{
		Node *son;
	public:
		NegaNode(Node *a) :
			son(a){}
		virtual void del(){
			son->del();
			delete son;
		}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "Negative Node" << endl;
			son->visit(x + 1);
		}
	};
	class ReturnNode :public Node{
		Node *son;
	public:
		ReturnNode(Node *a) :
			son(a){}
		virtual void del(){
			son->del();
			delete son;
		}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "Return Node" << endl;
			son->visit(x + 1);
		}
	};
	class ExprNode : public BinNode{
	public:
		ExprNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "Expr Node" << endl;
			this->visitson(x + 1);
		}
	};
	class EqNode : public BinNode{
	public:
		EqNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "Eq Node" << endl;
			this->visitson(x + 1);
		}
	};
	class NeqNode : public BinNode{
	public:
		NeqNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "Neq Node" << endl;
			this->visitson(x + 1);
		}
	};
	class GtNode : public BinNode{
	public:
		GtNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "Gt Node" << endl;
			this->visitson(x + 1);
		}
	};
	class NgtNode : public BinNode{
	public:
		NgtNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "Ngt Node" << endl;
			this->visitson(x + 1);
		}
	};
	class LtNode : public BinNode{
	public:
		LtNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "Lt Node" << endl;
			this->visitson(x + 1);
		}
	};
	class NltNode : public BinNode{
	public:
		NltNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "Nlt Node" << endl;
			this->visitson(x + 1);
		}
	};
	class StmtsNode : public BinNode{
	public:
		StmtsNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "stmts Node" << endl;
			this->visitson(x + 1);
		}
	};
	class ArgusNode : public BinNode{
	public:
		ArgusNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "ARGUS Node" << endl;
			this->visitson(x + 1);
		}
	};
	class GetSonNode : public BinNode{
	public:
		GetSonNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "GETSON Node" << endl;
			this->visitson(x + 1);
		}
	};
	class GetSubNode : public BinNode{
	public:
		GetSubNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "getsub Node" << endl;
			this->visitson(x + 1);
		}
	};
	class CallNode : public BinNode{
	public:
		CallNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "Call Node" << endl;
			this->visitson(x + 1);
		}
	};
	class AssignNode : public BinNode{
	public:
		AssignNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "Assign Node" << endl;
			this->visitson(x + 1);
		}
	};
	class FuncNode : public BinNode{
	public:
		FuncNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "Func Node" << endl;
			this->visitson(x + 1);
		}
	};
	class IfNode : public BinNode{
	public:
		IfNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "If Node" << endl;
			this->visitson(x + 1);
		}
	};
	class TriNode : public Node{
	public:
		Node * a, *b, *c;
		TriNode(Node *_a, Node * _b, Node *_c)
			:a(_a), b(_b), c(_c){}
		virtual void del(){
			a->del();
			b->del();
			c->del();
			delete a;
			delete b;
			delete c;
		}
		virtual void visitson(int x){
			a->visit(x);
			b->visit(x);
			c->visit(x);
		}
	};
	class IfElseNode : public TriNode{
	public:
		IfElseNode(Node *_cond, Node * _then, Node *_elsethen)
			:TriNode(_cond, _then, _elsethen){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "If ElseNode" << endl;
			this->visitson(x + 1);
		}
	};
	class ForNode :public Node{

	};
	class WhileNode : public BinNode{
	public:
		WhileNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "While Node" << endl;
			this->visitson(x + 1);
		}
	};
	class ArguDecNode : public BinNode{
	public:
		ArguDecNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "ArguDec Node" << endl;
			this->visitson(x + 1);
		}
	};
	class DecsNode : public BinNode{
	public:
		DecsNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "Decs Node" << endl;
			this->visitson(x + 1);
		}
	};
	class ArrDecNode : public BinNode{
	public:
		ArrDecNode(Node *l, Node *r)
			:BinNode(l, r){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "ArrDec Node" << endl;
			this->visitson(x + 1);
		}
	};
	class FuncDecNode : public TriNode{
	public:
		FuncDecNode(Node *_name, Node * _argus, Node *_stmts)
			:TriNode(_name, _argus, _stmts){}
		virtual void visit(int x){
			for (int i = 1; i <= x; i++)printf(" ");
			cout << "FuncDec Node" << endl;
			this->visitson(x + 1);
		}
	};
	Node *root;
public:
	Node* createBinNode(Node *l, Node *r, int id){
		switch (id){
		case LEX_ADD:return new AddNode(l, r); break;
		case LEX_SUB:return new SubNode(l, r); break;
		case LEX_MUL:return new MulNode(l, r); break;
		case LEX_DIV:return new DivNode(l, r); break;
		case LEX_MOD:return new ModNode(l, r); break;
		case LEX_EQ:return new EqNode(l, r); break;
		case LEX_NEQ:return new NeqNode(l, r); break;
		case LEX_GT:return new GtNode(l, r); break;
		case LEX_NGT:return new NgtNode(l, r); break;
		case LEX_LT:return new LtNode(l, r); break;
		case LEX_NLT:return new NltNode(l, r); break;
		}
	}
	void refresh(){
		if (root == 0)return;
		root->del();
		delete root;
		root = 0;
	}
	bool ParseStmts(){
		if (ParseStmt()){
			auto OriginStatus = lex.getNowPos();
			auto tmp = root;
			if (ParseStmts()){
				root = new StmtsNode(tmp, root);
				return 1;
			}
			else{
				root = tmp;
				return 1;
			}
		}
		else{
			return 0;
		}
	}
	bool ParseStmt(){
		auto OriginStatus = lex.getNowPos();
		auto x = lex.readNextToken();
		if (x.id == LEX_SEMI){
			root = new EmptyNode();
			return 1;
		}
		else if (x.id == LEX_LCB){
			if (ParseStmts()){
				auto y = lex.readNextToken();
				if (y.id == LEX_RCB){
					return 1;
				}
				else{
					refresh();
					lex.setNowPos(OriginStatus);
					errHandler.ThrowError(Err_NotMatched_CurlyBrace, lex.getNowLine());
					return 0;
				}
			}
			else{
				lex.setNowPos(OriginStatus);
				errHandler.ThrowError(Err_Expection_CurlyBrace, lex.getNowLine(), " { (cruly brace)");
				return 0;
			}
		}
		else if (x.id == LEX_VAR){
			if (ParseDecs()){
				auto y = lex.readNextToken();
				if (y.id == LEX_SEMI){
					return 1;
				}
				else{
					lex.setNowPos(OriginStatus);
					errHandler.ThrowError(Err_LackOf_Semi, lex.getNowLine(), "At the end of var statment");
					return 0;
				}
			}
			else{
				lex.setNowPos(OriginStatus);
				errHandler.ThrowError(Err_Expection_Token, lex.getNowLine(), "Var");
				return 0;
			}
		}
		else if (x.id == LEX_IF){
			auto y = lex.readNextToken();
			if (y.id == LEX_LP){
				if (ParseExpr()){
					auto z = lex.readNextToken();
					auto tmpRoot = root;
					if (z.id == LEX_RP){
						if (ParseStmt()){
							auto SecondStatus = lex.getNowPos();
							auto k = lex.readNextToken();
							if (k.id == LEX_ELSE){
								auto tmpSecondRoot = root;
								if (ParseStmt()){
									root = new IfElseNode(tmpRoot, tmpSecondRoot, root);
									return 1;
								}
								else{
									root = tmpRoot;
									refresh();
									root = tmpSecondRoot;
									refresh();
									lex.setNowPos(OriginStatus);
									return 0;
								}
							}
							else{
								lex.setNowPos(SecondStatus);
								root = new IfNode(tmpRoot, root);
								return 1;
							}
						}
						else{
							root = tmpRoot;
							refresh();
							lex.setNowPos(OriginStatus);
							return 0;
						}
					}
					else{
						refresh();
						lex.setNowPos(OriginStatus);
						return 0;
					}
				}
				else{
					lex.setNowPos(OriginStatus);
					return 0;
				}
			}
			else{
				lex.setNowPos(OriginStatus);
				return 0;
			}
		}
		else if (x.id == LEX_WHILE){
			auto y = lex.readNextToken();
			if (y.id == LEX_LP){
				if (ParseExpr()){
					auto z = lex.readNextToken();
					auto tmpRoot = root;
					if (z.id == LEX_RP){		
						if (ParseStmt()){
							root = new WhileNode(tmpRoot, root);
							return 1;
						}
						else{
							root = tmpRoot;
							refresh();
							lex.setNowPos(OriginStatus);
							return 0;
						}
					}
					else{
						refresh();
						lex.setNowPos(OriginStatus);
						return 0;
					}
				}
				else{
					lex.setNowPos(OriginStatus);
					return 0;
				}
			}
			else{
				lex.setNowPos(OriginStatus);
				return 0;
			}
		}
		else if (x.id == LEX_BREAK){
			auto y = lex.readNextToken();
			if (y.id == LEX_SEMI){
				root = new BreakNode();
				return 1;
			}
			else{
				lex.setNowPos(OriginStatus);
				errHandler.ThrowError(Err_LackOf_Semi, lex.getNowLine(), "At the end of Break statment");
				return 0;
			}
		}
		else if (x.id == LEX_CONTINUE){
			auto y = lex.readNextToken();
			if (y.id == LEX_SEMI){
				root = new ContinueNode();
				return 1;
			}
			else{
				lex.setNowPos(OriginStatus);
				errHandler.ThrowError(Err_LackOf_Semi, lex.getNowLine(), "At the end of Continue statment");
				return 0;
			}
		}
		else if (x.id == LEX_RETURN){
			if (ParseExpr()){
				auto y = lex.readNextToken();
				if (y.id == LEX_SEMI){
					root = new ReturnNode(new IdNode(x));
					return 1;
				}
				else{
					lex.setNowPos(OriginStatus);
					return 0;
				}
			}
			else{
				//?
			}
		}
		lex.setNowPos(OriginStatus);
		if (ParseID()){
			auto x = lex.readNextToken();
			auto tmpRoot = root;
			if (x.id == LEX_ASSIGN){
				if (ParseExpr()){
					auto y = lex.readNextToken();
					if (y.id == LEX_SEMI){
						root = new AssignNode(tmpRoot, root);
						return 1;
					}
							else{
								refresh();
								root = tmpRoot;
								refresh();
						lex.setNowPos(OriginStatus);
					}
				}
				else{
					root = tmpRoot;
					refresh();
					lex.setNowPos(OriginStatus);
				}
			}
			else{
				lex.setNowPos(OriginStatus);
			}
		}
		if (ParseExpr()){
			auto x = lex.readNextToken();
			if (x.id == LEX_SEMI){
				//?
				return 1;
			}
			else{
				refresh();
				lex.setNowPos(OriginStatus);
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	bool ParseDecs(){
		if (ParseDec()){
			auto OriginStatus = lex.getNowPos();
			auto tmp = root;
			auto x = lex.readNextToken();
			if (x.id == LEX_COM){
				auto SecondStauts = lex.getNowPos();
				if (ParseDecs()){
					root = new DecsNode(tmp, root);
					return 1;
				}
				else{
					root = tmp;
					refresh();
					lex.setNowPos(OriginStatus);
					return 0;
				}
			}
			else{
				lex.setNowPos(OriginStatus);
				return 1;
			}
		}
		else{
			return 0;
		}
	}
	bool ParseDec(){
		auto OriginStatus = lex.getNowPos();
		auto x = lex.readNextToken();
		if (x.id == LEX_ID){
			auto SecondStatus = lex.getNowPos();
			auto y = lex.readNextToken();
			if (y.id == LEX_ASSIGN){
				auto ThirdStauts = lex.getNowPos();
				auto w = lex.readNextToken();
				if (w.id == LEX_GT){
					auto z = lex.readNextToken();
					if (z.id == LEX_LP){
						if (ParseArguDecs()){
							auto k1 = lex.readNextToken();
							auto k2 = lex.readNextToken();
								if (k1.id == LEX_RP && k2.id == LEX_LCB){
								auto tmpRoot = root;
								if (ParseStmts()){
									auto k3 = lex.readNextToken();
										if (k3.id == LEX_RCB){
										root = new FuncDecNode(new IdNode(x), tmpRoot, root);
										return 1;
									}
									else{
										refresh();
										root = tmpRoot;
										refresh();
										lex.setNowPos(OriginStatus);
										return 0;
									}
								}
								else{
									root = tmpRoot;
									refresh();
									lex.setNowPos(OriginStatus);
									return 0;
								}
							}
							else{
								refresh();
								lex.setNowPos(OriginStatus);
								return 0;
							}
						}
						else{
							lex.setNowPos(OriginStatus);
							return 0;
						}
					}
					else{
						lex.setNowPos(OriginStatus);
						return 0;
					}
				}
				else{
					lex.setNowPos(ThirdStauts);
				}
				if (ParseExpr()){
					return 1;
				}
				else{
					lex.setNowPos(SecondStatus);
					root = new IdDecNode(x);
					return 1;
				}
			}
			else if (y.id == LEX_LSB){
				auto z = lex.readNextToken();
				auto k = lex.readNextToken();
				if (z.id == LEX_NUMBER  && k.id == LEX_RSB){
					root = new ArrDecNode(new IdNode(x), new NumNode(z));
				}
				else{
					lex.setNowPos(SecondStatus);
					root = new IdDecNode(x);
					return 1;
				}
			}
			else{
				lex.setNowPos(SecondStatus);
				root = new IdDecNode(x);
				return 1;
			}
		}
		else{
			lex.setNowPos(OriginStatus);
			return 0;
		}
	}
	bool ParseArguDecs(){
		auto OriginStatus = lex.getNowPos();
		auto x = lex.readNextToken();
		if (x.id == LEX_ID){
			auto SecondStatus = lex.getNowPos();
			root = new IdNode(x);
			auto x = lex.readNextToken();
			if (x.id == LEX_COM){
				auto tmp = root;
				if (ParseArguDecs()){
					root = new ArguDecNode(tmp, root);
					return 1;
				}
				else{
					root = tmp;
					//surprise comma
					return 0;
				}
			}
			else{
				lex.setNowPos(SecondStatus);
				return 1;
			}	
		}
		else{
			lex.setNowPos(OriginStatus);
			root = new EmptyNode();
			return 1;
		}
	}
	bool ParseExpr(){
		if (ParseSum()){
			auto tmp = root;
			auto secondPos = lex.getNowPos();
			auto x = lex.readNextToken();
			if (x.id == LEX_EQ || x.id == LEX_NEQ || x.id == LEX_NLT ||
				x.id == LEX_NGT || x.id == LEX_GT || x.id == LEX_LT){
				if (ParseExpr()){
					root = createBinNode(tmp, root, x.id);
					return 1;
				}
				else{
					root = tmp;
					lex.setNowPos(secondPos);
					return 1;
				}
			}
			else{
				lex.setNowPos(secondPos);
				return 1;
			}
		}
		else{
			return 0;
		}
	}
	bool ParseSum(){
		auto OriginStatus = lex.getNowPos();
		if (ParseFact()){
			auto tmp = root;
			auto secondPos = lex.getNowPos();
			auto x = lex.readNextToken();
			if (x.id == LEX_ADD || x.id == LEX_SUB){
				if (ParseSum()){
					root = createBinNode(tmp, root, x.id);
					return 1;
				}
				else{
					root = tmp;
					lex.setNowPos(secondPos);
					return 1;
				}
			}
			else{
				lex.setNowPos(secondPos);
				return 1;
			}
		}
		else{
			return 0;
		}

	}
	bool ParseFact(){
		auto OriginStatus = lex.getNowPos();
		if (ParseUnit()){
			auto tmp = root;
			auto secondPos = lex.getNowPos();
			auto x = lex.readNextToken();
			if (x.id == LEX_DIV || x.id == LEX_MUL || x.id == LEX_MOD){
				if (ParseFact()){
					root = createBinNode(tmp, root, x.id);
					return 1;
				}
				else{
					root = tmp;
					lex.setNowPos(secondPos);
					return 1;
				}
			}
			else{
				lex.setNowPos(secondPos);
				return 1;
			}
		}
		else{
			return 0;
		}
	}
	bool ParseUnit(){
		auto OriginStatus = lex.getNowPos();
		auto x = lex.readNextToken();
		if (x.id == LEX_ADD || x.id == LEX_SUB){
			if (ParseValue()){
				if (x.id == LEX_SUB)root = new NegaNode(root);
				return 1;
			}
			else{
				lex.setNowPos(OriginStatus);
				return 0;
			}
		}
		else if (x.id == LEX_LP){
			if (ParseSum()){
				auto y = lex.readNextToken();
				if (y.id == LEX_RP){
					return 1;
				}
				else{
					refresh();
					lex.setNowPos(OriginStatus);
					return 0;
				}
			}
			else{
				lex.setNowPos(OriginStatus);
				return 0;
			}
		}
		else{
			lex.setNowPos(OriginStatus);
			if (ParseValue()){
				return 1;
			}
			else{
				return 0;
			}
		}
	}
	bool ParseArgus(){
		auto OriginStatus = lex.getNowPos();
		if (ParseExpr()){
			auto SecondStatus = lex.getNowPos();
			auto tmp = root;
			if (ParseArgus()){
				root = new ArgusNode(tmp, root);
				return 1;
			}
			else{
				root = tmp;
				return 1;
			}
		}
		else{
			return 0;
		}
	}
	bool ParseValue(){
		if (ParseID()){
			auto OriginStatus = lex.getNowPos();
			auto x = lex.readNextToken();
			auto tmpRoot = root;
			if (x.id == LEX_LCB){
				if (ParseArgus()){
					auto y = lex.readNextToken();
					if (y.id == LEX_RCB){
						root = new CallNode(tmpRoot, root);
					}
					else{
						refresh();
						lex.setNowPos(OriginStatus);
						root = tmpRoot;
						return 1;
					}
				}
				else{
					lex.setNowPos(OriginStatus);
					root = tmpRoot;
					return 1;
				}
			}
			else{
				lex.setNowPos(OriginStatus);
				return 1;
			}
		}
		else{
			auto OriginStatus = lex.getNowPos();
			auto x = lex.readNextToken();
			if (x.id == LEX_STRING){
				root = new StrNode(x);
				return 1;
			}
			else if (x.id == LEX_NUMBER){
				root = new NumNode(x);
				return 1;
			}
			else {
				lex.setNowPos(OriginStatus);
				return 0;
			}
		}
	}
	bool ParseOBJID(){
		//wait
		return 0;
	}
	bool ParseID(){
		auto OriginStatus = lex.getNowPos();
		auto x = lex.readNextToken();
		if (x.id == LEX_ID){
			auto SecondStatus = lex.getNowPos();
			auto y = lex.readNextToken();
			if (y.id == LEX_LSB){
				if (ParseExpr()){
					auto z = lex.readNextToken();
					if (z.id == LEX_RSB){
						root = new GetSubNode(new IdNode(x), root);
						return 1;
					}
					else{
						refresh();
						lex.setNowPos(SecondStatus);
						root = new IdNode(x);
						return 1;
					}
				}
				else{
					lex.setNowPos(SecondStatus);
					root = new IdNode(x);
					return 1;
				}
			}
			else{
				lex.setNowPos(SecondStatus);
				root = new IdNode(x);
				return 1;
			}
		}
		else{
			lex.setNowPos(OriginStatus);
			return 0;
		}
	}
	bool test(){
		
	}
	Parser(Lex &_lex)
		:lex(_lex){
	}
};
void out(Token a){
	cout << a.id << " " << a.name << " " << a.line << endl;
	return;
}

int main(){
	Lex lex("test.ws");
	Parser ps(lex);
	while (ps.test());
	//for (int i = 1; i <= 30; i++)
	//	out(lex.readNextToken());
	return 0;
}