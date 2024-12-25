package Java;

import java.util.ArrayList;
import java.util.List;

public class Inventory<T extends Item> {
    private List<T> items;

    public Inventory() {
        items = new ArrayList<>();
    }

    public void addItem(T item) {
        items.add(item);
    }

    public void removeItem(int index) {
        if (index >= 0 && index < items.size()) {
            items.remove(index);
        }
    }

    public T getItem(int index) {
        return items.get(index);
    }

    public int size() {
        return items.size();
    }

    public String getDescription() {
        StringBuilder result = new StringBuilder("Inventory:\n");
        for (T item : items) {
            result.append("- ").append(item.getName()).append("\n");
        }
        return result.toString();
    }

    public List<T> getItems() {
        return new ArrayList<>(items);
    }
}
