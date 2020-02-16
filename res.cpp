#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+5;
struct warehouse{
    int id;
    int row,col;
    vector<int> numberOfProducts;
};
struct product{
    int id;
    int weight;
};
struct order{
    int id;
    int row,col;
    //first - id of product, second - number of products
    vector<pair<int,int>>products;  
    double distFromWareHouse;
};
struct drone{
    int id,currx,curry,currCapacity;
    void load(int warehouseId,int productType,int numberOfProducts){
        cout<<id<<" L "<<warehouseId<<" "<<productType<<" "<<numberOfProducts<<"\n";
    }
    void deliver(int customerId,int productType,int numberOfProducts){
        cout<<id<<" D "<<customerId<<" "<<productType<<" "<<numberOfProducts<<"\n";
    }
    int time;
};
int summ(vector<pair<int,int>>products){
    int sum=0;
    for(int i=0;i<products.size();i++){
        sum+=products[i].second;
    }
    return sum;
}
int dist(int x1,int y1,int x2,int y2){
    double an= sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    int ans=ceil(an);
    return ans;
}
vector<product> products;
vector<warehouse> warehouses;
vector<order> orders;
vector<drone> drones;
int rows,cols,droneNumber,timeEnd,droneLoad;
int numOfProducts,numOfWarehouses,numOfOrders;
int main(){
    freopen("qualification_round_2016.in/test.in","r",stdin);
	//freopen("resenje.txt","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>rows>>cols>>droneNumber>>timeEnd>>droneLoad;
    //cout<<"rows:"<<rows<<", cols:"<<cols<<"\n";
    cin>>numOfProducts;
    for(int i=0;i<numOfProducts;i++){
        product newProduct;
        newProduct.id=i;
        cin>>newProduct.weight;
        products.push_back(newProduct);
    }
    /*for(auto&x:products){
        cout<<"product:"<<"\n";
        cout<<"id:"<<x.id<<" "<<" weight:"<<x.weight<<"\n";
    }*/
    cin>>numOfWarehouses;
    for(int i=0;i<numOfWarehouses;i++){
        warehouse newWarehouse;
        newWarehouse.id=i;
        int row,col,prods;
        cin>>row>>col;
        newWarehouse.row=row;
        newWarehouse.col=col;
        vector<int> numOfProds;
        for(int i=0;i<numOfProducts;i++){
            int numOfp;
            cin>>numOfp;
            numOfProds.push_back(numOfp);
        }
        newWarehouse.numberOfProducts=numOfProds;
        warehouses.push_back(newWarehouse);
    }
    /*for(auto&x:warehouses){
        cout<<"warehouse:\n";
        cout<<"id:"<<x.id<<" row:"<<x.row<<" col:"<<x.col<<"\n";
        cout<<"products:\n";
        for(int i=0;i<x.numberOfProducts.size();i++){
            cout<<x.numberOfProducts[i]<<'\n';
        }
    }*/
    cin>>numOfOrders;
    for(int i=0;i<numOfOrders;i++){
        order newOrder;
        newOrder.id=i;
        int row,col;
        cin>>row>>col;
        newOrder.row=row;
        newOrder.col=col;
        vector<pair<int,int>>numOfProds;
        int num;
        cin>>num;
        for(int i=0;i<num;i++){
            int productType;
            cin>>productType;
            bool ok=false;
            for(int i=0;i<numOfProds.size();i++){
                if(numOfProds[i].first==productType){
                    ok=true;
                    numOfProds[i].second++;
                    break;
                }
            }
            if(!ok){
                numOfProds.push_back(make_pair(productType,1));
            }
        }
        newOrder.products=numOfProds;
        orders.push_back(newOrder);
    }
  /*or(auto&x:orders){
        cout<<"id:"<<x.id<<"row: "<<x.row<<"col: "<<x.col<<"\n";
        for(auto&y:x.products){
            cout<<"type: "<<y.first<<"number :"<<y.second<<"\n";
        }
    }*/
    //cout<<"ok\n";
   
    for(auto& ord:orders){
        ord.distFromWareHouse=1e9;
        for(auto& ware:warehouses){
            int d=dist(ord.row,ord.col,ware.row,ware.col);
            if(ord.distFromWareHouse>d)
                ord.distFromWareHouse=d;
        }
    }

    sort(orders.begin(),orders.end(),[](order a,order b){
        return a.distFromWareHouse<b.distFromWareHouse;
    });
    /*for(auto&x:orders){

        cout<<"id:"<<x.id<<" row: "<<x.row<<" col: "<<x.col<<"\n";
        for(auto&y:x.products){
            cout<<"type: "<<y.first<<" number :"<<y.second<<"\n";
        }
        //for(int i=0;i<drones;)
    }*/
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    for(int i=0;i<droneNumber;i++){
        int returnTime=100;
        drone curr;
        curr.id=i;
        curr.currx=0;
        curr.curry=0;
        curr.time=0;
        curr.currCapacity=0;
        pq.push(make_pair(i,returnTime));
    }
    for(auto&x:orders){
        int currId=pq.top().first;
        drone currDrone=drones[currId];
        if(summ(x.products)+currDrone.currCapacity>droneLoad){
            pq.pop();
            int returnTime=currDrone.time;
            pq.push(make_pair(currId,returnTime));
        }
        for(auto&y:x.products){
            currDrone.load(0,y.first,y.second);
        }
        currDrone.deliver(0,y.first,y.second);
    }
    return 0;
}