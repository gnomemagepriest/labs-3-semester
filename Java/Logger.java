package Java;

import java.util.ArrayList;
import java.util.List;

public class Logger {
    private List<String> logs;

    public Logger() {
        logs = new ArrayList<>();
    }

    public void addLine(String newLine) {
        if (newLine.charAt(newLine.length() - 1) != '\n') {
            newLine += '\n';
        }
        logs.add(newLine);
    }

    public String getLastEvents() {
        if (logs.isEmpty()) {
            return "";
        }

        StringBuilder result = new StringBuilder();

        int size = logs.size();
        if (size > 1) {
            result.append(logs.get(size - 2));
        }
        result.append(logs.get(size - 1));

        return result.toString();
    }
}
