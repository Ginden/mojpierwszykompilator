    pointer = (0) | 0;
    heap[pointer] = (heap[pointer]) + 1;
    heap[pointer] = (heap[pointer]) + 1;
    heap[pointer] = (heap[pointer]) + 1;
    pointer += 1;
    heap[pointer] = (heap[pointer]) + 1;
    pointer += -1;
    while (heap[pointer] != 0) {
        heap[pointer] = (heap[pointer]) + -1;
        pointer += 1;
        heap[pointer] = (heap[pointer]) + 1;
        heap[pointer] = (heap[pointer]) + 1;
        heap[pointer] = (heap[pointer]) + 1;
        heap[pointer] = (heap[pointer]) + 1;
        pointer += -1;
    }
