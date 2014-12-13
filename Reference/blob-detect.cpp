#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include <queue>

using namespace std;
using namespace cv;

typedef struct pt_{
	int x,y;
}pt;

typedef struct blob_{
	int min_x,max_x;
	int min_y,max_y;
	int cen_x,cen_y;
	int n_pixels;
	int ID;
}blob;

void GetBlobs(Mat img, vector<blob>& blobs){
	int bot_center_x=0,bot_center_y=0; 	//Bot Center Initialized to (0,0)
	int i,j,k,l,r = img.rows,c = img.cols,id=1;	//r = rows, c = columnss
	vector<vector<int> > pixel_ID(r,vector<int>(c,-1)); //Stores ID of a pixel; -1 means unvisited = 2-Dimensional Array 
	queue<pt> open_list; //Breadth-First-Search hence queue of points

	for(i=1;i<r-1;i++){
		for(j=1;j<c-1;j++){
			if(img.at<uchar>(i,j)==0||pixel_ID[i][j]>-1)	
				continue;
			pt start = {j,i};		//(x,y)

			open_list.push(start); //Enqueue Start Point
			int sum_x=0,sum_y=0,n_pixels=0,max_x=0,max_y=0;	
			int min_x = c+1, min_y=r+1;
			while(!open_list.empty()){
				//Dequeue the element at the head of the queue
				pt top = open_list.front();
				open_list.pop();
				pixel_ID[top.y][top.x] = id;
				n_pixels++;

				//To obtain the bounding box of the blob w.r.t the original image
				min_x = (top.x<min_x)?top.x:min_x;
				min_y = (top.y<min_y)?top.y:min_y;
				max_x = (top.x>max_x)?top.x:max_x;
				max_y = (top.y>max_y)?top.y:max_y;
				sum_y+=top.y; sum_x+=top.x;

				//Add the 8-connected neighbours that are yet to be visited, to the queue
				for(k=top.y-1;k<=top.y+1;k++){
					for(l=top.x-1;l<=top.x+1;l++){
						if(img.at<uchar>(k,l)==0||pixel_ID[k][l]>-1)
							continue;
						pt next = {l,k};
						pixel_ID[k][l] = id;
						open_list.push(next);
					}
				}
			}
			if(n_pixels < 20) //At least 20 pixels
				continue;
			blob nextcentre = {min_x,max_x,min_y,max_y,sum_x/n_pixels,sum_y/n_pixels,id};
			blobs.push_back(nextcentre);
			id++;
		}
	}
	for(vector<blob>::iterator it=blobs.begin(); it!=blobs.end(); ++it )
	{
		// cout << it->min_x << " " << it->max_x << endl;
		// cout << it->min_y << " " << it->max_y <<endl ;
		// cout << it->cen_x << " " << it->cen_y << endl;
		bot_center_x += it->cen_x;
		bot_center_y += it->cen_y;
	}
	cout<<(bot_center_x / 6)<< " " << (bot_center_y/6) <<endl;
	cout<<blobs.size(); //To test correctness; can use the vector as desired
}

int main(){

	string fname;
    cout<<"Enter name of file:";
    cin>>fname;
    Mat image = imread(fname,0);

    vector<blob> blobs;
    GetBlobs(image,blobs);
    return 0; 


}
