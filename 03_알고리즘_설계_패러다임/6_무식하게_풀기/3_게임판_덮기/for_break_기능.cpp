#include <iostream>

int main(void)
{
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            std::cout << "i:" << i << ", j:" << j << ' ';
            if( i == 3 && j == 1 )
            {
                break;
            }
        }
        std::cout << std::endl;
    }
}