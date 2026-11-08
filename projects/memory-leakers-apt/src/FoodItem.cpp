#include "FoodItem.h"

FoodItem::FoodItem(std::string id, const std::string& name,
                   const std::string& description, float price)
    : id(id), name(name), description(description), price(price) {}

FoodItem::~FoodItem() {}

std::string FoodItem::getId() const { return id; }

std::string FoodItem::getName() const { return name; }

std::string FoodItem::getDescription() const { return description; }

float FoodItem::getPrice() const { return price; }

bool FoodItem::operator==(const FoodItem& other) const {
    return id == other.id && name == other.name &&
           description == other.description && price == other.price;
}
