#include <iostream>
#include <math.h>

int main()
{    
	int row = 10;
    int col = 10;
    int image[row][col];
    float ima_fi[row][col];
    int n;
	int mn;
	n = 5;
    int K[n][n];
    int Damp_fact = 1;
    float Weight[n][n];
    float container[n][n];
    
    for (int x=0; x<row; x++){
      for (int y=0; y<col; y++){
      		image[x][y] = 1;
      }
    }
    
   
    mn = (n - 1)/2;
	
    //Meshgrid
    
    int x_[n][n];
    int y_[n][n];
    
    int adder = 0;
    for (int x=0; x<n; x++){
    	for (int y=0; y<n; y++){
        	if (adder <= 2*mn){
            	x_[y][x] = (-1*mn) + adder;
            	y_[x][y] = (-1*mn) + adder;
            }
        }
        adder++;
    }


  // Calculate S Matrix 
  
    double S[n][n];
  
    for (int x=0; x<n; x++){
    	for (int y=0; y<n; y++){
			S[x][y] = sqrt((x_[x][y]*x_[x][y]) + (y_[x][y]*y_[x][y]));
        }
    }

    int padding_image[(row + 2*mn)][(col + 2*mn)];
    for (int x=0; x<((row + 2*mn)); x++){
      for (int y=0; y<((col + 2*mn)); y++){
				padding_image[x][y] = 0;
            }
      }

int i = 0;
int j = 0;

// Trying to padd the matrix with zeros border

	for (int x=0; x<((row + 2*mn)); x++){
    	for(int y=0; y<((col + 2*mn)); y++){
			if (((x >=mn) && (i<(row))) && ((y>=mn) && (j < (col)))){
					padding_image[x][y] = image[i][j];
					if ((j+1) % (col) == 0){
						i++;
					}
					j++;
				}
    	}
        j=0;
        
    }

    
    for (int row=0; row<n; row++){
        for (int col=0; col<n; col++){
            K[row][col] = 0;
        }
    }
    
    int count;
    int a_ = 0;
    int b_ = 0;
    int n_ = 0;
    int m_ = 0;
    count =  0;
    for (int x=0; x<row; x++){
    	for (int y=0; y<col; y++){
              for (int a=0; a<n; a++){
                  for (int b=0; b<n; b++){
					  if ((n_ < (col + mn)) &&(m_ < (row + mn)) ){
                          K[a][b] = padding_image[a_][b_];
						  if ((count + 1)%n == 0){
                              count = 0;
                              if (( a_ + 1)% (n + m_) == 0){
                                                if ((n_) == ((col + (2*mn) - n))){
                                                    n_ = 0;
                                                    m_++;
                                                    a_ = m_;
                                                    b_ = n_; 
                                                }else{
                                                    n_ ++;
                                                    m_ = m_;
                                                    b_ = n_;
                                                    a_ = m_;
                                                }
                              } else {
                                  a_ ++;
                                  //b_ = 0;
                                  b_ = n_;
                              }
                          }else{
                              count++;
                              b_++;
                          }


							  
					  }
					  
					  
					  
					  
                  }
              }


    float counter;
    float buffer;
    float means;
    for (int x1=0; x1<n; x1++){
      for (int y1=0; y1<n; y1++){
      		buffer += K[x1][y1];
            counter++;

      }
    }
    //means = (buffer/counter);

	means = buffer/counter;
    counter = 0.0;
    buffer = 0.0;

    // calculate variance
    float variance;
    for (int x1=0; x1<n; x1++){
      for (int y1=0; y1<n; y1++){
        buffer += ((K[x1][y1] - means)*(K[x1][y1] - means));
        counter++;
      }
    }
        variance = buffer/counter;
        buffer = 0.0;
        counter = 0.0;

    // calculate the weight of local window
    float B ;
    //float Weigh;
    B = Damp_fact*(variance/((means)*(means)));

    //calculate -B*S , it will be used for determining the weigh of local window
    for (int x1=0; x1<n; x1++){
      for (int y1=0; y1<n; y1++){
        container[x1][y1] = (-B*S[x1][y1]);

      }
    } 


    // Calculate Weigh matrix
    for (int x1=0; x1<n; x1++){
      for (int y1=0; y1<n; y1++){
        Weight[x1][y1] = (exp(container[x1][y1]));
      }
    } 
    

    float sum_K_Wgh;
    float sum_W;
    // generate the estimated image
    for (int x_=0; x_<n; x_++){
       for (int y_=0; y_<n; y_++){
           sum_K_Wgh += (K[x_][y_]*Weight[x_][y_]);
           sum_W += Weight[x_][y_];
       }
    }
    ima_fi[x][y] = sum_K_Wgh/sum_W;
    sum_K_Wgh = 0;
    sum_W = 0;
       
        }

    }
    
	// print value of filtered image
    for (int x=0; x<row; x++){
       for (int y=0; y<col; y++){
       		std::cout<<ima_fi[x][y]<<"    ";
       		if ((y+1)%col == 0){
              std::cout<<"\n";
             }
       }
    }
    
    std::cout<<"\n";
    
    return 0;
}




