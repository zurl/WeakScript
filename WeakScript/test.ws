{
	var a;var i;var j;var n;var flag;
	for(i=2;i<=1000;i=i+1){
		flag = 0;
		for(j=2;j<i;j=j+1){
			if(i % j == 0){
				flag = 1;
				break;
			}
		}
		if(flag == 0){
			print(i);
			print(" ");
		}
	}
}