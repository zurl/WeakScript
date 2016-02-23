ADD 0 -> 1val1
ADD 1 -> 2val2
ADD 2 -> 3val3
ADD 1 -> 4val4
ADD 4 -> 5val3
ADD 0 -> 1val6
ADD 1 -> 2val7
ADD 2 -> 3val8
ADD 1 -> 4val9
ADD 4 -> 5val8
ADD 0 -> 1val11
ADD 0 -> 2val12
ADD 2 -> 3val13
ADD 3 -> 4val14
class Node{
public:
	virtual void visit(int x) = 0;
	virtual void del() = 0;
};
class UnitNode : public Node{
public:
	UnitNode(){}
	void visitson(int x){}
	virtual void del(){}
};
class UnaryNode : public Node{
	Node *son;
public:
	UnaryNode(Node *_s)
	:son(_s){}
	void visitson(int x){
		son->visit(x);
	}
	virtual void del(){
		son->del();
		delete son;
	}
};
class BinaryNode : public Node{
	Node *left, *right;
public:
	BinaryNode(Node *_l, Node *_r)
	:left(_l), right(_r){}
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
class TernaryNode : public Node{
	Node *left, *mid,*right;
public:
	TernaryNode(Node *_l,Node *_m, Node *_r)
	:left(_l),mid(_m), right(_r){}
	void visitson(int x){
		left->visit(x);
		mid->visit(x);
		right->visit(x);
	}
	virtual void del(){
		left->del();
		mid->del();
		right->del();
		delete left;
		delete mid;
		delete right;
	}
};
Node *root;
void refresh(){
	if (root == nullptr)return;
	root->del();
	delete root;
	root = 0;
}
class NumNode : public Unary {
public:
	NumNode(Node *l, Node *r)
	:Unary(l, r) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("Unary");
		cout << "Num Node" << endl;
		this->visitson(x + 1);
	}
}

bool parseSum(){
	auto savedRoot1 = root;
	if ( parseFact() ){
		return 1;
	}
	else{
		refresh();
		root = savedRoot1;
		return 0;
	}
}
bool parseFact(){
	auto savedRoot1 = root;
	if ( parseUnit() ){
		return 1;
	}
	else{
		refresh();
		root = savedRoot1;
		return 0;
	}
}
bool parseUnit(){
	auto SavedLexPos1 = lex.getNowPos();
	auto ReadinToken1 = lex.readNextToken();
	if ( ReadinToken1.id == LEX_LCB ){
		auto savedRoot2 = root;
		if ( parseSum() ){
			auto SavedLexPos3 = lex.getNowPos();
			auto ReadinToken3 = lex.readNextToken();
			if ( ReadinToken3.id == LEX_RCB ){
				return 1;
			}
			else{
				lex.setNowPos(ReadinToken3);
				return 0;
			}
		}
		else{
			refresh();
			root = savedRoot2;
			return 0;
		}
	}
	else{
		lex.setNowPos(ReadinToken1);
		return 0;
	}
	auto SavedLexPos1 = lex.getNowPos();
	auto ReadinToken1 = lex.readNextToken();
	if ( ReadinToken1.id == LEX_num ){
		root = new NumNode(WTF);
		return 1;
	}
	else{
		lex.setNowPos(ReadinToken1);
		return 0;
	}
}

