vector<Rational> getMedian(vector<vector<Rational>>& v){

    vector<Rational> medians;

    for(auto i:v){
        int size=i.size();
        Rational temp;
        //bubble sort
        for(int j=0;j<size-1;j++){
            for(int k=0;k<size-1-j;k++){
                if(i[j+k+1]<i[j+k]){ //min to max
                    temp=i[j+k+1];
                    i[j+k+1]=i[j+k];
                    i[j+k]=temp;
                }
            }
        }

        if(size%2==1){
            medians.push_back(i[(size/2)+1]);
        }

        else{
            medians.push_back((i[(size/2)+1]+i[(size/2)-1])/2);
        }
    }
    return medians;
}