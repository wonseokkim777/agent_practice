#include "gilded_rose.h"

using std::vector;
using std::string;

namespace {
    constexpr int MAX_QUALITY = 50;
    constexpr int MIN_QUALITY = 0;

    const string AGED_BRIE       = "Aged Brie";
    const string BACKSTAGE_PASS  = "Backstage passes to a TAFKAL80ETC concert";
    const string SULFURAS        = "Sulfuras, Hand of Ragnaros";
    const string CONJURED_PREFIX = "Conjured";

    constexpr int BACKSTAGE_UPPER_THRESHOLD = 10;
    constexpr int BACKSTAGE_LOWER_THRESHOLD = 5;
}

GildedRose::GildedRose(vector<Item>& items) : items(items) {}

bool GildedRose::isAgedBrie(const Item& item)      { return item.name == AGED_BRIE; }
bool GildedRose::isSulfuras(const Item& item)      { return item.name == SULFURAS; }
bool GildedRose::isBackstagePass(const Item& item) { return item.name == BACKSTAGE_PASS; }
bool GildedRose::isConjured(const Item& item)      { return item.name.rfind(CONJURED_PREFIX, 0) == 0; }
bool GildedRose::isPastSellDate(const Item& item)  { return item.sellIn < 0; }

void GildedRose::increaseQuality(Item& item)
{
    if (item.quality < MAX_QUALITY)
        item.quality++;
}

void GildedRose::decreaseQuality(Item& item)
{
    if (item.quality > MIN_QUALITY)
        item.quality--;
}

void GildedRose::updateNormal(Item& item)
{
    decreaseQuality(item);
    item.sellIn--;
    if (isPastSellDate(item))
        decreaseQuality(item);
}

void GildedRose::updateAgedBrie(Item& item)
{
    increaseQuality(item);
    item.sellIn--;
    if (isPastSellDate(item))
        increaseQuality(item);
}

void GildedRose::updateBackstagePass(Item& item)
{
    increaseQuality(item);
    if (item.sellIn <= BACKSTAGE_UPPER_THRESHOLD)
        increaseQuality(item);
    if (item.sellIn <= BACKSTAGE_LOWER_THRESHOLD)
        increaseQuality(item);
    item.sellIn--;
    if (isPastSellDate(item))
        item.quality = MIN_QUALITY;
}

void GildedRose::updateConjured(Item& item)
{
    decreaseQuality(item);
    decreaseQuality(item);
    item.sellIn--;
    if (isPastSellDate(item))
    {
        decreaseQuality(item);
        decreaseQuality(item);
    }
}

void GildedRose::updateItem(Item& item)
{
    if (isSulfuras(item))      return;
    if (isAgedBrie(item))      { updateAgedBrie(item);      return; }
    if (isBackstagePass(item)) { updateBackstagePass(item); return; }
    if (isConjured(item))      { updateConjured(item);      return; }
    updateNormal(item);
}

void GildedRose::updateQuality()
{
    for (auto& item : items)
        updateItem(item);
}
