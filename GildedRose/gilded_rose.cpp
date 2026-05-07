#include "gilded_rose.h"

using std::vector;
using std::string;

GildedRose::GildedRose(vector<Item>& items) : items(items)
{
}

void GildedRose::increaseQuality(Item& item)
{
    if (item.quality < 50)
        item.quality++;
}

void GildedRose::decreaseQuality(Item& item)
{
    if (item.quality > 0)
        item.quality--;
}

void GildedRose::updateNormal(Item& item)
{
    decreaseQuality(item);
    item.sellIn--;
    if (item.sellIn < 0)
        decreaseQuality(item);
}

void GildedRose::updateAgedBrie(Item& item)
{
    increaseQuality(item);
    item.sellIn--;
    if (item.sellIn < 0)
        increaseQuality(item);
}

void GildedRose::updateBackstagePass(Item& item)
{
    increaseQuality(item);
    if (item.sellIn <= 10)
        increaseQuality(item);
    if (item.sellIn <= 5)
        increaseQuality(item);
    item.sellIn--;
    if (item.sellIn < 0)
        item.quality = 0;
}

void GildedRose::updateConjured(Item& item)
{
    decreaseQuality(item);
    decreaseQuality(item);
    item.sellIn--;
    if (item.sellIn < 0)
    {
        decreaseQuality(item);
        decreaseQuality(item);
    }
}

void GildedRose::updateItem(Item& item)
{
    if (item.name == "Sulfuras, Hand of Ragnaros")
        return;
    else if (item.name == "Aged Brie")
        updateAgedBrie(item);
    else if (item.name == "Backstage passes to a TAFKAL80ETC concert")
        updateBackstagePass(item);
    else if (item.name.rfind("Conjured", 0) == 0)
        updateConjured(item);
    else
        updateNormal(item);
}

void GildedRose::updateQuality()
{
    for (auto& item : items)
        updateItem(item);
}
