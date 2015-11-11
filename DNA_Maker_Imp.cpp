/*
DNA Sequence Generation and Comparison Project
Author:  John Wiseman

This program is designed to use multiple classes to generate Acid
chains of DNA Codons, and them compare them to one another to test
for similar sequences within the two chains, and to identify the
longest equivalent chains.
*/


#include "DNA_Maker.h"


///Codon Class Elements

codon::codon() //creator for the codon class
    {
       int r; //will store value of 0-3 created by a %4 of a random number to choose random letter
       for(int i=0; i<3; i++)  //creates a 3 letter group
       {
          r = rand()%4; //assigns random value from 0-3 to variable r
          switch(r) //uses value of r to select one of four possible letters
          {
              case 0:{C[i]='A';}break;
              case 1:{C[i]='T';}break;
              case 2:{C[i]='C';}break;
              case 3:{C[i]='G';}break;
          }
       }
       next = NULL;  //sets the "next" pointer to NULL.
    }

codon::~codon() //codon class' destructer
    {

    }

char codon::get_codon(int i)  //retrieves the value of a codon from the linked list to keep the program from revealing the array address.
    {
        char r = C[i];
        return r;
    }

bool codon::assess_codon()  //Assesses a codon node to see if it is a 'Stop' codon, which can only exist at the end of a codon chain.
    {
        bool isTrue = false;
        if((get_codon(0) == 'T' &&
           get_codon(1) == 'A' &&
           get_codon(2) == 'A')||   //first stop codon

           (get_codon(0) == 'T' &&
           get_codon(1) == 'A' &&
           get_codon(2) == 'G')||   //second stop codon

           (get_codon(0) == 'T' &&
           get_codon(1) == 'G' &&
           get_codon(2) == 'A'))    //third stop codon
           {
               isTrue = true;
               return isTrue;
           }
    }

codon* codon::get_nextCodon()   //function to get the next codon in the list
    {
        return next;
    }

 void codon::set_nextCodon(codon* ptr)  //function to assign the next codon in the list to the "next" pointer in a node
    {
        next = ptr;
    }


///Acid Class Elements

acid::acid()    //default constructer for the acid class, which is a chain of nodes made of the class codon
    {
        neew = NULL;    //defaults "neew" pointer to NULL.  Note... I just picked neew because 'new' is a reserved word, and it made it 4 characters long like the other two pointers...  It was a silly preference thing.
        head = neew;    //defaults "head" to the value of 'neew,' which at start is NULL.
        temp = neew;    //defaults "temp" to the value of 'neew,' which at start is NULL.
    }
acid::acid(int length) //constructor for acid class, which will actually generate a Linked List of codon nodes of the specified length.
    {
        neew = NULL;    //defaults "neew" pointer to NULL.
        head = neew;    //defaults "head" to the value of 'neew,' which at start is NULL.
        temp = neew;    //defaults "temp" to the value of 'neew,' which at start is NULL.
//            ///*********
        //<('.'<)  <('.')>  (>'.')>  ^(^.^)^  <('.'<)  <('.')>  (>'.')>// It's 2 AM.  Kirby dance.
        neew = new codon;   //creates a new codon node at acid's 'neew' pointer.
        ///*********
        while(neew->assess_codon())  //This is called after a new codon is created in the chain, and checks if it is a "STOP" codon.  If it is, this function will delete it and create another new one until it is NOT a STOP codon.
        {
            ///*********
            delete neew;
            neew = new codon;
        }

        temp = neew; //Iterates the temp to the new current node.
        head = neew; //Iterates head to neew, which should currently be the first node in a new Linked List
        for(int i = 1; i < length; i++)     //Starts creating the list of length 'length'
        {
            if(i < length - 1)  //Check to see if this is the last link in the chain.  If it is NOT, then...
            {
                neew = new codon;
                while(neew->assess_codon()) //Make sure it is NOT a STOP codon
                {
                    delete neew;
                    neew = new codon;
                }
                temp->set_nextCodon(neew); //Set Temp
                temp = neew;    //Iterate Temp
            }
            else                //Check to see if this is the last link in the chain.  If it IS, then...
            {
                neew = new codon;
                while(!neew->assess_codon())    //Make sure it IS a STOP codon
                {
                    delete neew;
                    neew = new codon;
                }
                temp->set_nextCodon(neew);  //Set temp
            }
        }
        temp = head; //The list should be finished at this point, so set temp back to the head of the list.
    }
acid::~acid() //default destructer
    {

    }
void acid::display_acid()   //Function to print out the LL of codons.
    {
        temp = head;
        int p = 1;
        while(temp->get_nextCodon() != NULL) //This will iterate through the full list, minus the final link.
        {
            cout << right << setw(4) << p << " [";
            for(int i = 0; i<3; i++)
            {
                cout << temp->get_codon(i) << ",";
            }
            cout << "]" << endl;
            p++;
            temp = temp->get_nextCodon();
        }
//This is here so it iterates one more time to cover the NULL link of the chain.
        cout << "STOP [";
        for(int i = 0; i<3; i++)
        {
            cout << temp->get_codon(i) << ",";
        }
        cout << "]" << endl;
    }
codon* acid::get_head() //Function to pass the head note through the program.
    {
        return head;
    }
void acid::acid_comparison(acid* a1, acid* a2)  //Function to compare two acid chains, and find the longest identical segment between the two of them
    {
        codon* curr_a1; //Creates current nodes for two chains
        codon* curr_a2;

        codon* temp_a1; //Creates temp nodes for two chains
        codon* temp_a2;

        codon* longestMatch_a1; //Creates starting point for longest match between two chains
        codon* longestMatch_a2;
        int longest = 0;

        curr_a1 = a1->get_head();   //Set current to the head of the first list.
        temp_a1 = curr_a1;

        curr_a2 = a2->get_head();   //Set current to the head of the second list.
        temp_a2 = curr_a2;

        char a;
        char b;
        char c;
        char x;
        char y;
        char z;

        int i = 0;
        int j = 0;
        int l = 0;

        while((curr_a1->get_nextCodon() != NULL)) //As long as we're not at the end of list 1
        {
            while((curr_a2->get_nextCodon() != NULL))   //As long as we're not at the end of list 2
            {
                    temp_a1 = curr_a1;  //Set first list's temp to the current
                    temp_a2 = curr_a2;  //Set second list's temp to the current.
                if((temp_a1->get_codon(0) == temp_a2->get_codon(0)) &&  //If the current codon of either list matches
                   (temp_a1->get_codon(1) == temp_a2->get_codon(1)) &&
                   (temp_a1->get_codon(2) == temp_a2->get_codon(2)))
                {
                    l = 1;  //Set the length of the match to 1

                    temp_a1 = temp_a1->get_nextCodon(); //Iterate to the next link of both lists
                    temp_a2 = temp_a2->get_nextCodon();
                    while((temp_a1->get_codon(0) == temp_a2->get_codon(0)) &&   //As long as they still match
                          (temp_a1->get_codon(1) == temp_a2->get_codon(1)) &&
                          (temp_a1->get_codon(2) == temp_a2->get_codon(2)))
                    {

                        temp_a1 = temp_a1->get_nextCodon(); //Move to the next link in both lists, and add one to "l"
                        temp_a2 = temp_a2->get_nextCodon();
                        l++;

                    }
                    if(l > longest) //if the current value of l is greater than the current value of length, then length gets l, and move to next link in the chains.
                    {

                        longest = l;

                        longestMatch_a1 = curr_a1;
                        longestMatch_a2 = curr_a2;
                    }
                        curr_a2 = curr_a2->get_nextCodon(); //Move to the next link in the second list, and start again.
                }
                else
                {

                    curr_a2 = curr_a2->get_nextCodon(); //Otherwise, JUST move to the next link in the second list.
                }

            }
            curr_a2 = a2->get_head();   //Start back at the beginning of list 2
            curr_a1 = curr_a1->get_nextCodon(); //and iterate the first list to its next link.
        }
        cout << endl;
        cout << "The longest link was " << longest << endl;  //Print the longest link.
        for(int i = 0; i < longest; i++)
        {
            cout << "["
                 << longestMatch_a1->get_codon(0) << ","
                 << longestMatch_a1->get_codon(1) << ","
                 << longestMatch_a1->get_codon(2) << "]"
                 << " =-= "
                 << "["
                 << longestMatch_a2->get_codon(0) << ","
                 << longestMatch_a2->get_codon(1) << ","
                 << longestMatch_a2->get_codon(2) << "]"
                 << endl;
                 longestMatch_a1 = longestMatch_a1->get_nextCodon();
                 longestMatch_a2 = longestMatch_a2->get_nextCodon();
        }

    }
