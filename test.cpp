#include"Real.h"
#include"Integer.h"
#include"LinearAlgebra.h"
#include<iostream>

usingnamespacestd;

voidtest1(){
Real::default_precision=30;
Reale(2);
Realterm(1);
for(inti=2;i<20;i++){
term/=Real(i);
e+=term;
}
cout<<e<<endl;
}

voidtest2(){
autoA=rand_real_matrix<Real>(5,5);
autoB=A.inv();
autoC=A*B;
cout<<A<<endl<<B<<endl<<C<<endl;
}

intmain(){
test2();
return0;
}