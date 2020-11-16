#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include <ctime>
using namespace std;
class Card {
public:
    enum Suit { diamonds, clubs, hearts, spades };
    enum Rank { ace = 1, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king };
    Card(Rank r = ace, Suit s = diamonds) : m_suit(s), m_rank(r) { m_IsFaceUp = true; }
    ~Card() {}
    void Flip() { m_IsFaceUp = !m_IsFaceUp; }
    int GetValue() const { return (m_IsFaceUp) ? (m_rank > 10) ? 10 : m_rank : 0; }
    friend ostream& operator<< (ostream& out, const Card& card);
private:
    Suit m_suit;
    Rank m_rank;
    bool m_IsFaceUp;
};
class Hand {
protected:
    vector<Card*> m_Cards;
public:
    Hand() { m_Cards.reserve(5); }
    virtual ~Hand() { Clear(); }
    inline void Add(Card* pCard) { m_Cards.push_back(pCard); }
    void Clear() { 
        for (auto* c : m_Cards) { delete c; c = nullptr; }
        m_Cards.clear();
    }
    int GetTotal() const {
        if (m_Cards.empty()) { return 0; }
        if (m_Cards.at(0)->GetValue() == 0) { return 0; }
        int total = 0;
        for (const auto* c : m_Cards) { total += c->GetValue(); }
        bool containsAce = false;
        for (const auto* c : m_Cards) {
            if (c->GetValue() == 0) { containsAce = true; }
        }
        if (containsAce && total <= 11) { total += 10; }
        return total;
    }
};
class GenericPlayer : public Hand {
protected:
    string name;
public:
    GenericPlayer(string n): name(n) {}
    virtual ~GenericPlayer() {}
    virtual bool IsHitting() const = 0;
    bool isBoosted() { return (GetTotal() > 21); }
    void Bust() { if(isBoosted()) cout << name << " Busts! " << GetTotal() << endl; }
    friend ostream& operator<< (ostream& out, const GenericPlayer& player);
};
class Player : public GenericPlayer {
public:
    Player(string n = "Player"): GenericPlayer(n) {}
    ~Player() {}
    bool IsHitting() const {
        char ans;
        cout << "Take card? (y/n): "; 
        cin >> ans;
        return (ans == 'y');
    }
    void Win() const { cout << name << " Win!" << endl; }
    void Lose() const { cout << name << " Lose!" << endl; }
    void Push() const { cout << name << " Pushes!" << endl; }
};
class House : public GenericPlayer {
public:
    House(string n = "House"): GenericPlayer(n) {}
    ~House() {}
    bool IsHitting() const { return (GetTotal() <= 16); }
    void FlipFirstCard() {
        if (!(m_Cards.empty())) { m_Cards[0]->Flip(); }
        else { cout << "No card to flip!\n"; }
    }

};
class Deck :public Hand {
public:
    Deck() { m_Cards.reserve(52); Populate(); }
    ~Deck(){}
    void Populate(){
        Clear();
        for (int s = Card::diamonds; s <= Card::spades; ++s) {
            for (int r = Card::ace; r <= Card::king; ++r) {
                Add(new Card(static_cast<Card::Rank>(r), static_cast<Card::Suit>(s)));
            }
        }
    }
    void Shuffle() { random_shuffle(begin(m_Cards), end(m_Cards)); }
    void Deal(Hand& aHand){
        if (!m_Cards.empty()) {
            aHand.Add(m_Cards.back());
            m_Cards.pop_back();
        }
        else { cout << "Out of cards. Unable to deal." << endl; }
    }
    void AdditionalCards(GenericPlayer& aPlayer){
        while (!(aPlayer.isBoosted()) && aPlayer.isBoosted())
        {
            Deal(aPlayer);
            cout << aPlayer << endl;
            if (aPlayer.isBoosted()) { aPlayer.Bust(); }
        }
    }
};
class Game {
private:
    Deck m_deck;
    House m_house;
    vector<Player> players;
public:
    Game(vector<string>& names) {
        for (const auto& a : names) { players.push_back(Player(a)); }
        srand(static_cast<unsigned int>(time(0)));
        m_deck.Populate();
        m_deck.Shuffle();
    }
    ~Game(){}
    void play() {
        for (int i = 0; i < 2; ++i) {
            for (auto& a : players) { m_deck.Deal(a); }
            m_deck.Deal(m_house);
        }
        m_house.FlipFirstCard();
        for (const auto& a : players) { cout << a << endl; }
        cout << m_house << endl;
        for (auto& a : players) { m_deck.AdditionalCards(a); }
        m_house.FlipFirstCard();
        cout << endl << m_house;
        m_deck.AdditionalCards(m_house);

        if (m_house.isBoosted()) {
            for (auto& a : players) { if (!a.isBoosted()) { a.Win(); } }
        }
        else {
            for (auto& a : players) {
                if (!a.isBoosted()) {
                    if (a.GetTotal() > m_house.GetTotal()) a.Win();
                    else if (a.GetTotal() < m_house.GetTotal()) a.Lose();
                    else a.Push();
                }
            }
        }
        for (auto& a : players) a.Clear();
        m_house.Clear();
    }
};
ostream& operator<< (ostream& out, const Card& card) {
    const string RANKS[] = { "0", "ace", "2", "3", "4", "5", "6", "7", "8", "9","10", "jack", "queen", "king" };
    const string SUITS[] = { "diamonds", "clubs", "hearts", "spades" };
    if (card.m_IsFaceUp) out << RANKS[card.m_rank] << " " << SUITS[card.m_suit];
    else out << "XX";
    return out;
}

ostream& operator<< (ostream& out, const GenericPlayer& player) {
    out << player.name << '\t';
    vector<Card*>::const_iterator pCard;
    if (!player.m_Cards.empty()) {
        for (pCard = player.m_Cards.begin(); pCard != player.m_Cards.end(); ++pCard) out << *(*pCard) << "\t";
        if (player.GetTotal() != 0) out << "Points: " << player.GetTotal() << endl;
    } else out << "empty";
    return out;
}
vector<string> getPlNames()
{
    int numPlayers = 0;
    while (numPlayers < 1 || numPlayers > 7)
    {
        cout << "How many players? (1-7):\n";
        cin >> numPlayers;
    }
    vector<string> names(numPlayers);
    string name;
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Enter name for player " << i + 1 << ": ";
        cin >> name;
        names.at(i) = name;
    }
    return names;
}
int main()
{
    cout << "\t\tWelcome to blackjack!\n\n";
    vector<string> names = getPlNames();
    cout << '\n';
    Game aGame(names);
    char again = 'y';
    while (again != 'n' && again != 'N')
    {
        aGame.play();
        cout << "\n Do you want to play again? (Y/N):\n";
        cin >> again;
    }
    return 0;
}