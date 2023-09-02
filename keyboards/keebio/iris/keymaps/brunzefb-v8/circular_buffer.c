

#define BUFFER_SIZE 30

typedef struct {
    uint16_t buffer[BUFFER_SIZE];
    int head;  // points to the first element
    int tail;  // points to the next empty slot
} CircularBuffer;

void InitializeBuffer(CircularBuffer* cb) {
    cb->head = 0;
    cb->tail = 0;
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        cb->buffer[i] = 0;
    }

}

bool IsBufferFull(CircularBuffer* cb) {
    return (cb->tail + 1) % BUFFER_SIZE == cb->head;
}

bool IsBufferEmpty(CircularBuffer* cb) {
    return cb->head == cb->tail;
}

void AddKeystroke(CircularBuffer* cb, char ch) {
    if (IsBufferFull(cb)) {
        // Remove the oldest element to make space
        cb->head = (cb->head + 1) % BUFFER_SIZE;
    }

    cb->buffer[cb->tail] = ch;
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
}

void TypeBuffer(CircularBuffer* cb) {
    int i = cb->head;
    while (true) {
        if (cb->buffer[i] > SAFE_RANGE) {
            continue;
        }
        tap_code16(cb->buffer[i]);
        if (i == cb->tail) {
            break;
        }
        i = (i + 1) % BUFFER_SIZE;
    }
}

void GetBuffer(CircularBuffer* cb, char* key, int key_len) {
    int pos = 0;
    memset(key, 0, key_len - 1);
    int i = cb->head;
    while (pos < key_len - 1) {
        if (cb->buffer[i] >= KC_A && cb->buffer[i] <= KC_Z) {
            key[pos++] = (char) (cb->buffer[i] - KC_A + 'a');
        }

        if (i == cb->tail) {
            break;
        }
        i = (i + 1) % BUFFER_SIZE;
    }
}

