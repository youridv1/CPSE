#include <array>
#include <iostream>

template<typename T, int N>
class mySet {
    protected:
        std::array<T, N> values;
        int size;

    public:
        mySet(){ size = 0; }

        void add(const T i){
            if(size < N){
                if( !contains(i) ){
                    values[size] = i;
                    size++;
                }
            }
        }

        void remove(const T i){
            if( size > 0 ){
                for( size_t j = 0; j < size - 1; j++ ){ // doesn't check last element, because the removal mechanism is different in that case
                    if( values[j] == i ){
                        values[j] = values[size - 1];
                        size--;
                    }
                }
                if( values[size - 1] == i){ // check last element
                    size--;
                }
            }
        }

        bool contains(const T i){
            for(size_t j = 0; j < size; j++){
                if(values[j] == i){
                    return true;
                }
            }
            return false;
        }

        friend std::ostream & operator<<( std::ostream& lhs, const mySet& rhs){
            for(size_t i = 0; i < rhs.size; i++ ){
                lhs << rhs.values[i] << ' ';
            }
            return lhs;
        }
};
