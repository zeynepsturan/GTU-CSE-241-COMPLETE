bool isSorted(const int array[], int size){
  
  if(size<3)
    return true;

  //check for max to min
  for(int i=0; i<size; i++){
    
    if(array[i]<array[i+1])
        return false;
  }

  //check for min to max
  for(int i=0; i<size; i++){
    
    if(array[i]>array[i+1])
      return false;
  }
  
  return true;
}
