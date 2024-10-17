int preIncInt(int *number){
    (*number)+=1;
    return (*number);
}

int postIncInt(int *number){
    (*number)+=1;
    return (*number)-1;
}
