#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

// Selecting two prime numbers
long long int a=2;
long long int p=10007;     //1000000007


// Function to compute power of 'a' mod p
long long int power(long long int a, long long int b,long long int P)
{
    if (b==1)
        return a;

    else
        return ((a*((long long int)power(a, b-1,p)))% P);
}


//--------------------------------------------
class Member{

    long long int priv_key;             //private key of node
    vector<long long int> priv_array;   //array to store private keys of ancestors


    public:
    Member *left;                       //pointer to left child
    Member *right;                      //pointer to right child

    long long int pub_key;              //public key of node

    // display private key array
    void dispArray(){
        for(long long int i=0; i<priv_array.size(); i++){
            cout<<priv_array[i]<<" ";
        }
        cout<<endl;
    }

    // generating private key of parent
    long long int genPrivateKey(long long int pubKey){
        return power(pubKey,priv_key,p);
    }

    void arrayAppend(long long int privKey){
        priv_array.push_back(privKey);
    }

    // visit all leaf nodes
    void visitChildren(Member *A){

        if(A->left==NULL){
            A->arrayAppend(priv_key);
            return;
        }
        else{
            visitChildren(A->left);
            visitChildren(A->right);
        }
    }

    /////////////// LEAF NODE Constructor
    Member(long long int n){
        left=NULL;
        right=NULL;
        priv_key=n;
        pub_key=power(a,priv_key,p);
    }

    /////////////// NON_LEAF NODE Constructor
    Member(Member *l, Member *r){
        left=l;
        right=r;
        priv_key=left->genPrivateKey(right->pub_key);
        pub_key=power(a,priv_key,p);
        visitChildren(this);
    }
};


//---------------------------------
int main(){

    // LEAF NODES
    Member E(2);
    Member F(3);
    Member G(4);
    Member H(5);
    Member I(6);

    // NON-LEAF NODES
    Member D(&H,&I);
    Member B(&D,&E);
    Member C(&F,&G);
    Member A(&B,&C);

    // DISPLAY GROUP KEYS
    H.dispArray();
    I.dispArray();
    E.dispArray();
    F.dispArray();
    G.dispArray();


    return 0;
}
