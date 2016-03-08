{  
	var parent = {
		a : "nb"
	};
	var son = {
		b : "sb"
	};
	son.__proto__ = parent;
	print(son.a);
}  