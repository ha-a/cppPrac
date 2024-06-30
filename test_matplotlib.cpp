#include "matplotlibcpp.h"
void main()
{
  // 第一引数はX軸の値、第二引数はY軸の値を設定。
  matplotlibcpp::plot({2, 2}); 
 
  // 図の表示指示。
  matplotlibcpp::show();   
}