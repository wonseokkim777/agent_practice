#include "gmock/gmock.h"
#include "gilded_rose.h"

using std::vector;
using std::string;
using ::testing::Eq;
using ::testing::Ge;
using ::testing::Le;
using ::testing::AllOf;

// --- Normal Items ---

TEST(NormalItemTest, DegradesQualityByOneBeforeSellDate) {
    vector<Item> items = { Item("Normal Item", 5, 10) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Eq(9));
    EXPECT_THAT(app.items[0].sellIn, Eq(4));
}

TEST(NormalItemTest, DegradesQualityByTwoAfterSellDate) {
    vector<Item> items = { Item("Normal Item", 0, 10) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Eq(8));
}

TEST(NormalItemTest, QualityNeverGoesNegativeBeforeSellDate) {
    vector<Item> items = { Item("Normal Item", 5, 0) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Ge(0));
}

TEST(NormalItemTest, QualityNeverGoesNegativeAfterSellDate) {
    vector<Item> items = { Item("Normal Item", -1, 1) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Ge(0));
}

// --- Aged Brie ---

TEST(AgedBrieTest, IncreasesQualityByOneBeforeSellDate) {
    vector<Item> items = { Item("Aged Brie", 5, 10) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Eq(11));
    EXPECT_THAT(app.items[0].sellIn, Eq(4));
}

TEST(AgedBrieTest, IncreasesQualityByTwoAfterSellDate) {
    vector<Item> items = { Item("Aged Brie", 0, 10) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Eq(12));
}

TEST(AgedBrieTest, QualityNeverExceedsFiftyBeforeSellDate) {
    vector<Item> items = { Item("Aged Brie", 5, 50) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Le(50));
}

TEST(AgedBrieTest, QualityNeverExceedsFiftyAfterSellDate) {
    vector<Item> items = { Item("Aged Brie", -1, 49) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Le(50));
}

// --- Sulfuras ---

TEST(SulfurasTest, QualityNeverChanges) {
    vector<Item> items = { Item("Sulfuras, Hand of Ragnaros", 5, 80) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Eq(80));
}

TEST(SulfurasTest, SellInNeverChanges) {
    vector<Item> items = { Item("Sulfuras, Hand of Ragnaros", 5, 80) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].sellIn, Eq(5));
}

// --- Backstage Passes ---

TEST(BackstagePassTest, IncreasesQualityByOneWhenMoreThanTenDays) {
    vector<Item> items = { Item("Backstage passes to a TAFKAL80ETC concert", 15, 10) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Eq(11));
}

TEST(BackstagePassTest, IncreasesQualityByTwoWhenTenDaysOrLess) {
    vector<Item> items = { Item("Backstage passes to a TAFKAL80ETC concert", 10, 10) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Eq(12));
}

TEST(BackstagePassTest, IncreasesQualityByThreeWhenFiveDaysOrLess) {
    vector<Item> items = { Item("Backstage passes to a TAFKAL80ETC concert", 5, 10) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Eq(13));
}

TEST(BackstagePassTest, QualityDropsToZeroAfterConcert) {
    vector<Item> items = { Item("Backstage passes to a TAFKAL80ETC concert", 0, 40) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Eq(0));
}

TEST(BackstagePassTest, QualityNeverExceedsFifty) {
    vector<Item> items = { Item("Backstage passes to a TAFKAL80ETC concert", 5, 49) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Le(50));
}

TEST(BackstagePassTest, SellInDecreasesByOne) {
    vector<Item> items = { Item("Backstage passes to a TAFKAL80ETC concert", 10, 10) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].sellIn, Eq(9));
}

// --- Conjured Items ---

TEST(ConjuredItemTest, DegradesQualityByTwoBeforeSellDate) {
    vector<Item> items = { Item("Conjured Mana Cake", 5, 10) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Eq(8));
    EXPECT_THAT(app.items[0].sellIn, Eq(4));
}

TEST(ConjuredItemTest, DegradesQualityByFourAfterSellDate) {
    vector<Item> items = { Item("Conjured Mana Cake", 0, 10) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Eq(6));
}

TEST(ConjuredItemTest, QualityNeverGoesNegativeBeforeSellDate) {
    vector<Item> items = { Item("Conjured Mana Cake", 5, 1) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Ge(0));
}

TEST(ConjuredItemTest, QualityNeverGoesNegativeAfterSellDate) {
    vector<Item> items = { Item("Conjured Mana Cake", -1, 3) };
    GildedRose app(items);
    app.updateQuality();
    EXPECT_THAT(app.items[0].quality, Ge(0));
}

// --- Quality bounds (multi-item) ---

TEST(QualityBoundsTest, QualityAlwaysNonNegative) {
    vector<Item> items = {
        Item("Normal Item", 5, 0),
        Item("Normal Item", -1, 0),
    };
    GildedRose app(items);
    app.updateQuality();
    for (const auto& item : app.items) {
        EXPECT_THAT(item.quality, Ge(0));
    }
}

TEST(QualityBoundsTest, QualityNeverExceedsFiftyForNonSulfurasItems) {
    vector<Item> items = {
        Item("Aged Brie", 5, 50),
        Item("Backstage passes to a TAFKAL80ETC concert", 5, 50),
    };
    GildedRose app(items);
    app.updateQuality();
    for (const auto& item : app.items) {
        EXPECT_THAT(item.quality, AllOf(Ge(0), Le(50)));
    }
}
