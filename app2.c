typedef unsigned int uint;
typedef char *string;

typedef struct {
    uint length;
    void *elements;
} Vector;

typedef struct {
    string key;
    string value;
} Pair;

typedef struct _Element {
    string tag;
    Vector props;
    string text;
} Element;

void toXml(string buffer, Element el) {
    uint p = 0;
    buffer[p++] = '<';
}

void render(string buffer) {
    Pair pairs[1] = { "style", "color: red;" };
    Vector props = { 1, pairs };
    Element header = { "h2", props, "Hello World" };

    toXml(buffer, header);
}
