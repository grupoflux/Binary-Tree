#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>


  enum nodeColor {
        RED,
        BLACK
  };


  typedef struct rbNode {
        int data, color, quantity;
        float price;        
        char rank[1];                
        struct rbNode *link[2];
  }tree;

  struct rbNode *root = NULL;

  struct rbNode *createNode(int data, int quantity, float price) {
        struct rbNode *newnode;
        newnode = (struct rbNode *)malloc(sizeof(struct rbNode));
        newnode->data = data;
        newnode->color = RED;
        newnode->price = price;
        newnode->quantity = quantity;

        //Inserção do rank padrão do cliente novo.
        if (price < 5) {

                newnode->rank[0] = 'B';

        } else if (price >= 5 && price < 10) {

                newnode->rank[0] = 'M';

        } else {

                newnode->rank[0] = 'C';

        }
                
        newnode->link[0] = newnode->link[1] = NULL;
        return newnode;
  }

  void insertion (int data, int quantity, float price) {
        struct rbNode *stack[98], *ptr, *newnode, *xPtr, *yPtr;
        int dir[98], ht = 0, index;
        //printf("oi."); //breakpoint 1
        ptr = root;
        if (!root) {
                //printf("O problema está aqui."); // breakpoint 2
                root = createNode(data, quantity, price);
                return;
        }
        //printf("crisis core.");
        stack[ht] = root;
        dir[ht++] = 0;
        /* find the place to insert the new node */
        while (ptr != NULL) {
                if (ptr->data == data) {
                        printf("Duplicates Not Allowed!!\n");
                        return;
                }
                index = (data - ptr->data) > 0 ? 1 : 0;
                stack[ht] = ptr;
                ptr = ptr->link[index];
                dir[ht++] = index;
        }
        /* insert the new node */
        stack[ht - 1]->link[index] = newnode = createNode(data, quantity, price);
        while ((ht >= 3) && (stack[ht - 1]->color == RED)) {
                if (dir[ht - 2] == 0) {
                        yPtr = stack[ht - 2]->link[1];
                        if (yPtr != NULL && yPtr->color == RED) {
                                /*
                                 * Red node having red child. B- black, R-red
                                 *     B                R
                                 *    / \             /   \
                                 *   R   R  =>     B     B
                                 *  /               /   
                                 * R               R
                                 */
                                stack[ht - 2]->color = RED;
                                stack[ht - 1]->color = yPtr->color = BLACK;
                                ht = ht -2;
                        } else {
                                if (dir[ht - 1] == 0) {
                                        yPtr = stack[ht - 1];
                                } else {
                                        /*
                                         * XR - node X with red color
                                         * YR - node Y with red color
                                         * Red node having red child
                                         *(do single rotation left b/w X and Y)
                                         *         B             B
                                         *        /             /
                                         *      XR     =>      YR
                                         *        \           /
                                         *         YR        XR
                                         * one more additional processing will be
                                         * performed after this else part.  Since
                                         * we have red node (YR) with red child(XR)
                                         */
                                        xPtr = stack[ht - 1];
                                        yPtr = xPtr->link[1];
                                        xPtr->link[1] = yPtr->link[0];
                                        yPtr->link[0] = xPtr;
                                        stack[ht - 2]->link[0] = yPtr;
                                }
                                /*
                                 *  Red node(YR) with red child (XR) - single
                                 *  rotation b/w YR and XR for height balance. Still,
                                 *  red node (YR) is having red child.  So, change the
                                 *  color of Y to black and Black child B to Red R
                                 *          B           YR          YB
                                 *         /           /  \        /  \
                                 *        YR  =>   XR   B  =>  XR  R
                                 *       /
                                 *      XR
                                 */
                                xPtr = stack[ht - 2];
                                xPtr->color = RED;
                                yPtr->color = BLACK;
                                xPtr->link[0] = yPtr->link[1];
                                yPtr->link[1] = xPtr;
                                if (xPtr == root) {
                                        root = yPtr;
                                } else {
                                        stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                                }
                                break;
                        }
                } else {
                        yPtr = stack[ht - 2]->link[0];
                        if ((yPtr != NULL) && (yPtr->color == RED)) {
                                /*
                                 * Red node with red child
                                 *        B             R
                                 *      /   \         /   \
                                 *     R     R =>  B     B
                                 *             \              \
                                 *              R              R
                                 *
                                 */
                                stack[ht - 2]->color = RED;
                                stack[ht - 1]->color = yPtr->color = BLACK;
                                ht = ht - 2;
                        } else {
                                if (dir[ht - 1] == 1) {
                                        yPtr = stack[ht - 1];
                                } else {
                                        /*
                                         * Red node(XR) with red child(YR) 
                                         *   B          B
                                         *    \          \
                                         *     XR  => YR
                                         *    /            \
                                         *   YR             XR
                                         * Single rotation b/w XR(node x with red color) & YR
                                         */
                                        xPtr = stack[ht - 1];
                                        yPtr = xPtr->link[0];
                                        xPtr->link[0] = yPtr->link[1];
                                        yPtr->link[1] = xPtr;
                                        stack[ht - 2]->link[1] = yPtr;
                                }
                                /*
                                 *   B              YR          YB
                                 *    \             /  \        /  \
                                 *     YR  =>   B   XR => R    XR
                                 *      \
                                 *       XR
                                 * Single rotation b/w YR and XR and change the color to
                                 * satisfy rebalance property.
                                 */
                                xPtr = stack[ht - 2];
                                yPtr->color = BLACK;
                                xPtr->color = RED;
                                xPtr->link[1] = yPtr->link[0];
                                yPtr->link[0] = xPtr;
                                if (xPtr == root) {
                                        root = yPtr;
                                } else {
                                        stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                                }
                                break;
                        }
                }
        }
        root->color = BLACK;
  }


  int AddToArray(tree *node, tree arr[], int i)
{
     if(node == NULL)
          return i;


     arr[i].data = node -> data;
     arr[i].price = node -> price;
     arr[i].quantity = node -> quantity;
     
     i++;
     if(node->link[0] != NULL)
          i = AddToArray(node->link[0], arr, i);
     if(node->link[1] != NULL)
          i = AddToArray(node->link[1], arr, i);

     return i;
}

int compare(const void * a, const void * b){
    return ( *(int*)a - *(int*)b ); 
}


  int main(){

        int data, quantity, price;
        tree arr[5];
        char postArray[1000];

        FILE* stream = fopen("ds.csv", "r");

        while (fscanf(stream, "%d%*c%d%*c%d", &data, &quantity, &price) == 3) {
                insertion(data, quantity, price);
        }        
        
        AddToArray(root, arr, 0);
        qsort(arr, 5, sizeof(arr[0]), compare);
        for(int j = 0; j < 3; j++){        
                char strData[50], strQuantity[50], strPrice[50];
                strcat(postArray, "[");
                snprintf(strData, 50, "%d", arr[j].data );
                strcat(postArray, strData);
                strcat(postArray, ",");
                snprintf(strQuantity, 50, "%d", arr[j].quantity);
                strcat(postArray, strQuantity);
                strcat(postArray, ",");
                snprintf(strPrice, 50, "%f", arr[j].price);
                strcat(postArray, strPrice); 
                strcat(postArray, "],");
        }

        printf(postArray);

        CURL *curl;
	CURLcode res;

        curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl == NULL)
	{
		return 128;
	}
	char dest[12];

	char *jsonObja = "rank=";
	strcpy(dest, jsonObja);
        strcpy(dest, postArray);

	char *jsonObj = dest;
	struct curl_slist *headers = NULL;
	curl_slist_append(headers, "Accept: application/json");
	curl_slist_append(headers, "Content-Type: application/json");
	curl_slist_append(headers, "charsets: utf-8");

	curl_easy_setopt(curl, CURLOPT_URL, "https://m9963ywzsg.execute-api.us-east-1.amazonaws.com/default/RecomendationSystem");

	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonObj);
	curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, main);
	res = curl_easy_perform(curl);

	curl_easy_cleanup(curl);
	curl_global_cleanup();

        printf("\n");

  }
  