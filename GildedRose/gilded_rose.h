#pragma once
#include <string>
#include <vector>

class Item
{
public:
    std::string name;
    int sellIn;
    int quality;
    Item(std::string name, int sellIn, int quality) : name{ name }, sellIn{ sellIn }, quality{ quality }
    {
    }
};

class GildedRose
{
public:
    std::vector<Item>& items;
    GildedRose(std::vector<Item>& items);

    void updateQuality();

private:
    void updateItem(Item& item);
    void updateNormal(Item& item);
    void updateAgedBrie(Item& item);
    void updateBackstagePass(Item& item);
    void updateConjured(Item& item);
    static void increaseQuality(Item& item);
    static void decreaseQuality(Item& item);
};