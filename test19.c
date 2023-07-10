#include <stdio.h>
#define CARDS 52

struct bitCard
{
    unsigned int face : 4;
    unsigned int suit : 2;
    unsigned int color : 1;
};


typedef struct bitCard Card;

void fillDeck(Card * const wDeck);
void deal(const Card * const wDeck);

int main (void)
{
    Card deck[CARDS];

    fillDeck(deck);

    puts("Card values 0-12 correspond to Ace through King");
    puts("Color values 0-4 correspond Hearts, Diamonds, Clubs, Spades");
    puts("Card values 0 and 1 correspond to Red and Black\n");
    deal(deck);
}

void fillDeck(Card * const wDeck)
{
    for (size_t i = 0; i < CARDS; ++i)
    {
        wDeck[i].face = i % (CARDS/4);
        wDeck[i].suit = i/(CARDS/4);
        wDeck[i].color = i/(CARDS/2);
    }
}

void deal(const Card * const wDeck)
{
    printf("%-6s%-6s%-15s%-6s%-6s%s\n","Card","Suit","Color","Card","Suit","Color");

    for(size_t i = 0, j = i + 26; i < CARDS/2; ++i, ++j)
    {
        printf("Card:%3d Suit:%3d Color:%2d",wDeck[i].face,wDeck[i].suit,wDeck[i].color);
        printf("Card:%3d Suit:%3d Color:%2d\n",wDeck[j].face,wDeck[j].suit,wDeck[j].color);
    }
}