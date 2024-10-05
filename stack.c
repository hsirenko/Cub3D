typedef struct s_coord {
    int x;
    int y;
} t_coord;

typedef struct s_stack {
    int len;
    int cap;
    t_coord* data;
} t_stack;

t_stack make_stack(int capacity) {
    t_stack stack;
    stack.cap = capacity;
    stack.len = 0;
    stack.data = calloc(capacity, sizeof(t_coord));
    return stack;
}

void push(t_stack* stack, t_coord coord) {
    if (stack->len >= stack->cap)
    {
        t_coord* new_data = calloc(stack->cap*2, sizeof(t_coord));
        memcpy(new_data, stack->data, stack->cap * sizeof(t_coord));
        stack->cap *= 2;
    }
    
    stack->data[stack->len] = coord;
}

int pop(t_stack* stack, t_coord* dst) {
    if (stack->len == 0) {
        return 0;
    }

    stack->len--;
    *dst = stack->data[stack->len];
    return 1;
}

t_coord new_coord(int x, int y) {
    t_coord c;
    c.x = x;
    c.y = y;
    return c;
}

int has_holes(char** map, int w, int h, int start_x, int start_y) {
    t_stack stack = make_stack(42);

    int** visited = calloc(h, sizeof(int*));
    for(int i = 0; i < h; i++) {
        visited[i] = calloc(w, sizeof(int));
    }

    push(&stack, new_coord(start_x, start_y));
    while(stack.len > 0) {
        t_coord curr;
        pop(&stack, &curr);

        t_coord neighbours[4];
        neighbours[0] = new_coord(curr.x - 1, curr.y);
        neighbours[1] = new_coord(curr.x + 1, curr.y);
        neighbours[2] = new_coord(curr.x, curr.y - 1);
        neighbours[3] = new_coord(curr.x, curr.y + 1);

        for(int i = 0; i < 4; i++) {
            t_coord neighbour = neighbours[i];
            if (neighbour.x < 0 || neighbour.y < 0 || neighbour.x >= w || neighbour.y >= h)
                return 1;
            if (map[neighbour.y][neighbour.x] == '0' && !visited[neighbour.y][neighbour.x]) {
                visited[neighbour.y][neighbour.x] = 1;
                push(&stack, neighbour);
            }
        }
    }
    return 0;
}