import java.util.*;
import java.util.concurrent.*;
import java.time.*;
import java.util.Optional;
import java.util.stream.Stream;

public class JavaTypes {

    // Using Object
    public static Object objectValue = new Object();

    // Null
    public static Object nullValue = null;

    // Bool
    public static boolean boolValue = true;

    // Int
    public static int intValue = 42;

    // i8 (byte in Java)
    public static byte i8Value = (byte) 8;

    // i16 (short in Java)
    public static short i16Value = 16;

    // i32 (int in Java)
    public static int i32Value = 32;

    // i64 (long in Java)
    public static long i64Value = 64L;

    // c32 (Java's char is UTF-16, so no direct equivalent for UTF-32)
    public static char c32Value = '\u0041'; // A

    // c16 (Java's char is UTF-16)
    public static char c16Value = '\u0042'; // B

    // c8 (byte used for ASCII or similar)
    public static byte c8Value = (byte) 67; // C

    // Float
    public static float floatValue = 3.14f;

    // Double
    public static double doubleValue = 3.14;

    // Queue
    public static Queue<Integer> queueValue = new LinkedList<>();

    // Deque
    public static Deque<Integer> dequeValue = new ArrayDeque<>();

    // String
    public static String stringValue = "Hello, world!";

    // Optional (from java.util.Optional)
    public static Optional<String> optionalValue = Optional.of("Optional Value");

    // Date (from java.util.Date, deprecated; use java.time.Instant instead)
    public static Instant dateValue = Instant.now();

    // Time (from java.time.LocalTime)
    public static LocalTime timeValue = LocalTime.now();

    // Stream (from java.util.stream.Stream)
    public static Stream<String> streamValue = Stream.of("stream", "example");

    public static void main(String[] args) {
        // Example usage
        System.out.println("Object: " + objectValue);
        System.out.println("Null: " + nullValue);
        System.out.println("Bool: " + boolValue);
        System.out.println("Int: " + intValue);
        System.out.println("i8: " + i8Value);
        System.out.println("i16: " + i16Value);
        System.out.println("i32: " + i32Value);
        System.out.println("i64: " + i64Value);
        System.out.println("c32: " + c32Value);
        System.out.println("c16: " + c16Value);
        System.out.println("c8: " + c8Value);
        System.out.println("Float: " + floatValue);
        System.out.println("Double: " + doubleValue);
        System.out.println("Queue: " + queueValue);
        System.out.println("Deque: " + dequeValue);
        System.out.println("String: " + stringValue);
        System.out.println("Optional: " + optionalValue.orElse("Empty"));
        System.out.println("Date: " + dateValue);
        System.out.println("Time: " + timeValue);
        System.out.println("Stream: ");
        streamValue.forEach(System.out::println);
    }
}

