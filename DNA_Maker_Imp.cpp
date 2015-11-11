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

codon::codon()
    {
       int r;
       for(int i=0; i<3; i++)
       {
          r = rand()%4;
          switch(r)
          {
              case 0:{C[i]='A';}break;
              case 1:{C[i]='T';}break;
              case 2:{C[i]='C';}break;
              case 3:{C[i]='G';}break;
          }
       }
       next = NULL;
    }

codon::~codon()
    {

    }

char codon::get_codon(int i)
    {
        char r = C[i];
        return r;
    }

bool codon::assess_codon()
    {
        bool isTrue = false;
        if((get_codon(0) == 'T' &&
           get_codon(1) == 'A' &&
           get_codon(2) == 'A')||

           (get_codon(0) == 'T' &&
           get_codon(1) == 'A' &&
           get_codon(2) == 'G')||

           (get_codon(0) == 'T' &&
           get_codon(1) == 'G' &&
           get_codon(2) == 'A'))
           {
               isTrue = true;
               return isTrue;
           }
    }

codon* codon::get_nextCodon()
    {
        return next;
    }

 void codon::set_nextCodon(codon* ptr)
    {
        next = ptr;
    }


///Acid Class Elements

acid::acid()
    {
        neew = NULL;
        head = neew;
        temp = neew;
    }
acid::acid(int length)
    {
        neew = NULL;
        head = neew;
        temp = neew;
//            ///*********
        //<('.'<)  <('.')>  (>'.')>  ^(^.^)^  <('.'<)  <('.')>  (>'.')>//
        neew = new codon;
        ///*********
        while(neew->assess_codon())
        {
            ///*********
            delete neew;
            neew = new codon;
        }

        temp = neew;
        head = neew;
        for(int i = 1; i < length; i++)
        {
            if(i < length - 1)
            {
                neew = new codon;
                while(neew->assess_codon())
                {
                    delete neew;
                    neew = new codon;
                }
                temp->set_nextCodon(neew);
                temp = neew;
            }
            else
            {
                neew = new codon;
                while(!neew->assess_codon())
                {
                    delete neew;
                    neew = new codon;
                }
                temp->set_nextCodon(neew);
            }
        }
        temp = head;
    }
acid::~acid()
    {

    }
void acid::display_acid()
    {
        temp = head;
        //char show = 'a';
        int p = 1;
        while(temp->get_nextCodon() != NULL)
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
codon* acid::get_head()
    {
        return head;
    }
void acid::acid_comparison(acid* a1, acid* a2)
    {
        codon* curr_a1;
        codon* curr_a2;

        codon* temp_a1;
        codon* temp_a2;

        codon* longestMatch_a1;
        codon* longestMatch_a2;
        int longest = 0;

        curr_a1 = a1->get_head();
        temp_a1 = curr_a1;

        curr_a2 = a2->get_head();
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

        while((curr_a1->get_nextCodon() != NULL))
        {
            while((curr_a2->get_nextCodon() != NULL))
            {
                    temp_a1 = curr_a1;
                    temp_a2 = curr_a2;
                if((temp_a1->get_codon(0) == temp_a2->get_codon(0)) &&
                   (temp_a1->get_codon(1) == temp_a2->get_codon(1)) &&
                   (temp_a1->get_codon(2) == temp_a2->get_codon(2)))
                {
                    l = 1;

                    temp_a1 = temp_a1->get_nextCodon();
                    temp_a2 = temp_a2->get_nextCodon();
                    while((temp_a1->get_codon(0) == temp_a2->get_codon(0)) &&
                          (temp_a1->get_codon(1) == temp_a2->get_codon(1)) &&
                          (temp_a1->get_codon(2) == temp_a2->get_codon(2)))
                    {

                        temp_a1 = temp_a1->get_nextCodon();
                        temp_a2 = temp_a2->get_nextCodon();
                        l++;

                    }
                    if(l > longest)
                    {

                        longest = l;

                        longestMatch_a1 = curr_a1;
                        longestMatch_a2 = curr_a2;
                    }
                        curr_a2 = curr_a2->get_nextCodon();
                }
                else
                {

                    curr_a2 = curr_a2->get_nextCodon();
                }

            }
            curr_a2 = a2->get_head();
            curr_a1 = curr_a1->get_nextCodon();
        }
        cout << endl;
        cout << "The longest link was " << longest << endl;
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
