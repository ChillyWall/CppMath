#ifndefMATRIX_H_
#defineMATRIX_H_1

#include<vector>
#include<string>
#include<memory>
#include<initializer_list>
#include<random>
#include<ctime>

template<typenameT>
classMatrix{
private:
template<typenameTp>
usingptr=std::unique_ptr<Tp>;
usingild=std::initializer_list<T>;
usingvd=std::vector<T>;
usingpd=ptr<ptr<T>[]>;

size_tm_=0;
size_tn_=0;
size_tsize_=0;

pddata_;

voidshape_check1(size_tm,size_tn)const;

public:
Matrix():data_{pd()}{}
Matrix(size_tm,size_tn);
Matrix(size_tm,size_tn,constild&data);
Matrix(size_tm,size_tn,constT&filling);
Matrix(constMatrix<T>&M);
Matrix(Matrix<T>&&M)noexcept:m_{M.m_},n_{M.n_},size_{M.size_}{
data_=std::move(M.data_);
}
~Matrix()=default;

voidset(constsize_tm,constsize_tn,constild&data){
set(m,n,vd(data));
}
voidset(constsize_tm,constsize_tn,ild&&data)noexcept{
set(m,n,vd(std::move(data)));
}
voidset(size_tm,size_tn,constvd&data);
voidset(size_tm,size_tn,vd&&data)noexcept;
voidfill(constT&filling);

size_tm()const{returnm_;}
size_tn()const{returnn_;}

size_tsize()const{returnsize_;}

Matrix<T>inv()const;
Tdet()const;
size_trank()const;

T&operator()(size_ti,size_tj);

constT&operator()(size_ti,size_tj)const;

Matrix<T>&operator=(constMatrix<T>&M);
Matrix<T>&operator=(Matrix<T>&&M)noexcept;

Matrix<T>operator+(constMatrix<T>&M)const;
Matrix<T>operator-(constMatrix<T>&M)const;
Matrix<T>operator*(constMatrix<T>&M)const;
Matrix<T>operator*(constT&c)const;


Matrix<T>&operator+=(constMatrix<T>&M);
Matrix<T>&operator+=(Matrix<T>&&M)noexcept{
return*this+=M;
}

Matrix<T>&operator-=(constMatrix<T>&M);
Matrix<T>&operator-=(Matrix<T>&&M){
return*this+=M;
}

Matrix<T>&operator*=(constT&c);

Matrix<T>transpose()const;
};

template<typenameT>
std::ostream&operator<<(std::ostream&os,Matrix<T>&M);

template<typenameT>
std::ostream&operator<<(std::ostream&os,Matrix<T>&&M)noexcept;

template<typenameT>
inlineMatrix<T>operator*(constT&c,constMatrix<T>&M){
returnM*=c;
}

template<typenameT>
Matrix<T>Identity(size_tn);
template<typenameT>
Matrix<T>rand_int_matrix(size_tm,size_tn);
template<typenameT>
Matrix<T>rand_real_matrix(size_tm,size_tn);
template<typenameT>
Matrix<T>diag_matrix(size_tn,std::vector<T>&data);

template<typenameT>
structLU_comp{
Matrix<T>L;
Matrix<T>U;
};

template<typenameT>
LU_comp<T>LU(constMatrix<T>&M);

template<typenameT>
structLDU_comp{
Matrix<T>L;
std::vector<T>D;
Matrix<T>U;
};

template<typenameT>
LDU_comp<T>LDU(constMatrix<T>&M);

template<typenameT>
structPLU_comp{
std::vector<size_t>P;
Matrix<T>L;
Matrix<T>U;
};

template<typenameT>
PLU_comp<T>PLU(constMatrix<T>&M);

template<typenameT>
Matrix<T>permutation_matrix(size_tm,size_tn,std::vector<size_t>P);

template<typenameT>
Matrix<T>exchange_rows(conststd::vector<size_t>&P,Matrix<T>&M);

template<typenameT>
inlineTabs(constT&n){
returnn<T(0)?(-n):n;
}

template<typenameT>
inlineboolif_square(Matrix<T>A){
returnA.m()==A.n();
}

template<typenameT>
Matrix<T>solve(Matrix<T>A,Matrix<T>b);

#include"LinearAlgebra.cpp.impl"

#endif