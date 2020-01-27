#include <array>
#include <iostream>

template<typename T, int N>
class mySet {
protected:
    std::array<T, N> array;
    int size;

public:
    mySet(){ array = {}; size = 0; }

    void add(const T i){
        if(size < N){
            if( !contains(i) ){
                array[size] = i;
                size++;
            }
        }
    }

    void remove(const T i){
        if( size > 0 ){
            for( size_t j = 0; j < size - 1; j++ ){ // doesn't check last element, because the removal mechanism is different in that case
                if( array[j] == i ){
                    array[j] = array[size - 1];
                    size--;
                }
            }
            if( array[size - 1] == i ){ // check last element
                size--;
            }
        }
    }

    bool contains(const T i){
        for( size_t j = 0; j < size; j++ ){
            if(array[j] == i){ // if element is equal to the one required
                return true;
            }
        }
        return false;
    }

    friend std::ostream & operator<<( std::ostream& lhs, const mySet& rhs){
        for(size_t i = 0; i < rhs.size; i++ ){
            lhs << rhs.array[i] << ' ';
        }
        return lhs;
    }

    T max(){
        auto max = array[0];
        for(size_t i = 1; i < size; i++){
            if(array[i] > max){
                max = array[i];
            }
        }
        return max;
    }
};
