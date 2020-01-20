#include <array>
#include <iostream>

class mySet {
    protected:
        std::array<int, 10> values;
        int size;

    public:
        mySet(){ size = 0; }

        void add(const int i){
            if(size < 10){
                if( !contains(i) ){
                    values[size] = i;
                    size++;
                }
            }
        }

        void remove(const int i){
            if( size > 0 ){
                for( int j = 0; j < size - 1; j++ ){ // doesn't check last element, because the removal mechanism is different in that case
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

        bool contains(const int i){
            for(int j = 0; j < size; j++){
                if(values[j] == i){
                    return true;
                }
            }
            return false;
        }

        friend std::ostream & operator<<( std::ostream& lhs, const mySet& rhs);
};

std::ostream & operator<<(std::ostream& lhs, const mySet& rhs){
    for(int i = 0; i < rhs.size; i++ ){
        lhs << rhs.values[i] << ' ';
    }
    return lhs;
}
