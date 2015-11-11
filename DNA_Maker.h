/*
DNA Sequence Generation and Comparison Project
Author:  John Wiseman

This program is designed to use multiple classes to generate Acid
chains of DNA Codons, and them compare them to one another to test
for similar sequences within the two chains, and to identify the
longest equivalent chains.
*/


#ifndef DNA_MAKER_H
#define DNA_MAKER_H

class codon
{
    public:
        codon();
        virtual ~codon();
        char get_codon(int i);
        bool assess_codon();
        codon* get_nextCodon();
        void set_nextCodon(codon* ptr);
    private:
        char C[3];
        codon* next;
};

class acid
{
    public:
        acid();
        acid(int length);
        virtual ~acid();
        void display_acid();
        codon* get_head();
        void acid_comparison(acid* a1, acid* a2);
    private:
        codon* neew;
        codon* head;
        codon* temp;
};

int makeRandom();

#endif // WISEMAN_DNA_HEADER_H
