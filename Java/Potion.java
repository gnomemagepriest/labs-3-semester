package Java;

public class Potion extends Item {
    private String color;
    private String effect;

    public Potion() {
        super("Potion");
        this.color = "Clear";
        this.effect = "Water";
        this.symbol = '{';
    }

    public Potion(String color, String effect) {
        super("Potion");
        this.color = color;
        this.effect = effect;
        this.symbol = '{';
    }

    @Override
    public String getName() {
        return color + " " + name + " of " + effect;
    }
}
