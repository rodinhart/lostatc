typedef unsigned int uint;
typedef char *string;

typedef struct {
    uint len;
    void *items;
} Vector;

typedef struct {
    string key;
    string value;
} Pair;

typedef struct _Element {
    string tag;
    Vector *props;
    string text;
} Element;

uint string_copy(string des, string src) {
    int p = 0;
    while (src[p] != 0) {
        des[p] = src[p];
        p++;
    }

    return p;
}

uint toXml(string buffer, Element *el) {
    uint p = 0;
    buffer[p++] = '<';
    p += string_copy(buffer + p, el->tag);

    for (int i = 0; i < el->props->len; i++) {
        buffer[p++] = ' ';
        Pair *pairs = (Pair *)el->props->items;
        Pair *pair = pairs + i;
        p += string_copy(buffer + p, pair->key);

        buffer[p++] = '=';
        buffer[p++] = '"';
        p += string_copy(buffer + p, pair->value);
        buffer[p++] = '"';
    }

    buffer[p++] = '>';

    return p;
}

uint render(string buffer) {
    Pair pairs[] = { "style", "color: red;", "foo", "bar" };
    Vector props = { sizeof(pairs) / sizeof(Pair), pairs };
    Element header = { "h2", &props, "Hello World" };

    return toXml(buffer, &header);
}
