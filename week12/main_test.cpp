#include "main.cpp"
#include "gtest/gtest.h"

const string STORE_FILE = "giftstore.txt";
const string ANDREW_FILE = "Andrew.txt";
const int ANDREW_BUDGET = 5000;
const int ANDREW_REMAINING = 2;
const vector<string> ANDREW_WISHES = {
    "cd A Darker Shade Of White by Navarone",
    "sport Skateboard",
    "game Mens erger je niet!",
    "game The settlers of Catan",
    "book The Fellowship of th Ring by J.R.R. Tolkien",
    "book The Two Towers by J.R.R. Tolkien",
    "book The Return of the King by J.R.R. Tolkien",
    "cd Human .||. Nature by Nightwish",
    "cd Concrete and Gold by Foo Fighters",
    "sport student bike"
};
const string BELLE_FILE = "Belle.txt";
const int BELLE_BUDGET = 2500;
const int BELLE_REMAINING = 102;
const vector<string> BELLE_WISHES = {
    "toy clay",
    "toy crayons",
    "toy markers",
    "toy sketchbook",
    "game Jenga",
    "game Mens erger je niet!",
    "game Catan Junior",
    "sport children's bike",
    "Wii U"
};
const string CHRIS_FILE = "Chris.txt";
const int CHRIS_BUDGET = 3000;
const int CHRIS_REMAINING = 3;
const vector<string> CHRIS_WISHES = {
    "Playstation 5",
    "Xbox One",
    "Wii U",
    "game Mens erger je niet!",
    "cd Nothing but the beat by David Guetta",
    "cd Synthesized by Junkie XL",
    "cd The 2nd law by Muse",
    "cd Concrete and Gold by Foo Fighters",
    "book Diary of a wimply kid part 1 by J. Kinney",
    "book Diary of a wimply kid part 2 by J. Kinney",
    "book Diary of a wimply kid part 3 by J. Kinney",
    "book Diary of a wimply kid part 4 by J. Kinney",
    "book Diary of a wimply kid part 5 by J. Kinney",
    "book Diary of a wimply kid part 6 by J. Kinney",
    "book Weaveworld by C. Barker",
    "game cards",
    "game Catan Junior"
};
const string DESIREE_FILE = "Desiree.txt";
const int DESIREE_BUDGET = 7500;
const int DESIREE_REMAINING = 3;
const vector<string> DESIREE_WISHES = {
    "book Fiese Ferien by J. Till",
    "book Fette Ferien by J. Till",
    "book Bitterschokolade by M. Pressler",
    "book Crazy by B. Lebert",
    "dvd Brave by Pixar",
    "dvd Wall-E by Pixar",
    "dvd Up by Pixar",
    "cd Concrete and Gold by Foo Fighters",
    "book El juego del angel by C.R. Zafon",
    "make-up lipstick",
    "make-up mascara",
    "make-up nail polish",
    "game Mens erger je niet!",
    "game The settlers of Catan",
    "sport student bike"
};
const string EDWARD_FILE = "Edward.txt";
const int EDWARD_BUDGET = 45000;
const int EDWARD_REMAINING = 3;
const vector<string> EDWARD_WISHES = {
    "dvd Avatar by James Cameron",
    "dvd Joker by Todd Phillips",
    "blu-ray Inside Out by Pixar",
    "cd Different Shades Of Blue by Joe Bonamassa",
    "cd Concrete and Gold by Foo Fighters",
    "book La sombra del viento by C.R. Zafon",
    "book El juego del angel by C.R. Zafon",
    "book 10 vrolijke verhalen by S. King",
    "sport adult bike",
    "book The Hobbit by J.R.R. Tolkien",
    "book The Silmarillion by J.R.R. Tolkien",
    "sport running shoes",
    "game Monopoly",
    "game Mens erger je niet!",
    "game The settlers of Catan",
    "Playstation 5",
    "book The Fellowship of th Ring by J.R.R. Tolkien",
    "book The Two Towers by J.R.R. Tolkien",
    "book The Return of the King by J.R.R. Tolkien"
};
const string FABIENNE_FILE = "Fabienne.txt";
const int FABIENNE_BUDGET = 20000;
const int FABIENNE_REMAINING = 303;
const vector<string> FABIENNE_WISHES = {
    "sport cross-country ski",
    "game Mens erger je niet!",
    "game The settlers of Catan",
    "cd Marco by Marco Borsato",
    "cd Als geen ander by Marco Borsato",
    "cd De waarheid by Marco Borsato",
    "cd De bestemming by Marco Borsato",
    "cd Luid en duidelijk by Marco Borsato",
    "cd Onderweg by Marco Borsato",
    "cd Dromen durven delen by Marco Borsato",
    "cd Duizend spiegels by Marco Borsato",
    "cd 30 by Adele",
    "sport mountainbike",
    "sport racing bike",
    "sport handball",
    "sport goalkeeper gloves",
    "sport football shoes",
    "Playstation 5"
};

TEST(load, andrew)
{
    WishList andrewWishList;
    ASSERT_TRUE(DataWish(ANDREW_FILE, andrewWishList));
    EXPECT_EQ(andrewWishList.budget, ANDREW_BUDGET);
    EXPECT_EQ(andrewWishList.items, ANDREW_WISHES);
}

TEST(load, belle)
{
    WishList belleWishList;
    ASSERT_TRUE(DataWish(BELLE_FILE, belleWishList));
    EXPECT_EQ(belleWishList.budget, BELLE_BUDGET);
    EXPECT_EQ(belleWishList.items, BELLE_WISHES);
}

TEST(load, chris)
{
    WishList chrisWishList;
    ASSERT_TRUE(DataWish(CHRIS_FILE, chrisWishList));
    EXPECT_EQ(chrisWishList.budget, CHRIS_BUDGET);
    EXPECT_EQ(chrisWishList.items, CHRIS_WISHES);
}

TEST(load, desiree)
{
    WishList desireeWishList;
    ASSERT_TRUE(DataWish(DESIREE_FILE, desireeWishList));
    EXPECT_EQ(desireeWishList.budget, DESIREE_BUDGET);
    EXPECT_EQ(desireeWishList.items, DESIREE_WISHES);
}

TEST(load, edward)
{
    WishList edwardWishList;
    ASSERT_TRUE(DataWish(EDWARD_FILE, edwardWishList));
    EXPECT_EQ(edwardWishList.budget, EDWARD_BUDGET);
    EXPECT_EQ(edwardWishList.items, EDWARD_WISHES);
}

TEST(load, fabienne)
{
    WishList fabienneWishList;
    ASSERT_TRUE(DataWish(FABIENNE_FILE, fabienneWishList));
    EXPECT_EQ(fabienneWishList.budget, FABIENNE_BUDGET);
    EXPECT_EQ(fabienneWishList.items, FABIENNE_WISHES);
}

TEST(compute_gifts, andrew)
{
    giftStore store;
    ASSERT_TRUE(DataGift(STORE_FILE, store));

    WishList andrewWishList;
    ASSERT_TRUE(DataWish(ANDREW_FILE, andrewWishList));

    vector<string> selectedGifts;
    int remainingBudget = gifts(store, andrewWishList, 0, selectedGifts);

    EXPECT_EQ(remainingBudget, ANDREW_REMAINING);
}

TEST(compute_gifts, belle)
{
    giftStore store;
    ASSERT_TRUE(DataGift(STORE_FILE, store));

    WishList belleWishList;
    ASSERT_TRUE(DataWish(BELLE_FILE, belleWishList));

    vector<string> selectedGifts;
    int remainingBudget = gifts(store, belleWishList, 0, selectedGifts);

    EXPECT_EQ(remainingBudget, BELLE_REMAINING);
}

TEST(compute_gifts, chris)
{
    giftStore store;
    ASSERT_TRUE(DataGift(STORE_FILE, store));

    WishList chrisWishList;
    ASSERT_TRUE(DataWish(CHRIS_FILE, chrisWishList));

    vector<string> selectedGifts;
    int remainingBudget = gifts(store, chrisWishList, 0, selectedGifts);

    EXPECT_EQ(remainingBudget, CHRIS_REMAINING);
}

TEST(compute_gifts, desiree)
{
    giftStore store;
    ASSERT_TRUE(DataGift(STORE_FILE, store));

    WishList desireeWishList;
    ASSERT_TRUE(DataWish(DESIREE_FILE, desireeWishList));

    vector<string> selectedGifts;
    int remainingBudget = gifts(store, desireeWishList, 0, selectedGifts);

    EXPECT_EQ(remainingBudget, DESIREE_REMAINING);
}

TEST(compute_gifts, edward)
{
    giftStore store;
    ASSERT_TRUE(DataGift(STORE_FILE, store));

    WishList edwardWishList;
    ASSERT_TRUE(DataWish(EDWARD_FILE, edwardWishList));

    vector<string> selectedGifts;
    int remainingBudget = gifts(store, edwardWishList, 0, selectedGifts);

    EXPECT_EQ(remainingBudget, EDWARD_REMAINING);
}

TEST(compute_gifts, fabienne)
{
    giftStore store;
    ASSERT_TRUE(DataGift(STORE_FILE, store));

    WishList fabienneWishList;
    ASSERT_TRUE(DataWish(FABIENNE_FILE, fabienneWishList));

    vector<string> selectedGifts;
    int remainingBudget = gifts(store, fabienneWishList, 0, selectedGifts);

    EXPECT_EQ(remainingBudget, FABIENNE_REMAINING);
}
