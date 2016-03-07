{  
	var data = function(){
		for(var i=2;i<=1000;i=i+1){  
			var flag = 0;  
			for(var j=2;j<i;j=j+1){  
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
	};
	data();
}  