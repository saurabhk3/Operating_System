#include<unistd.h>
#include<stddef.h>
#include<stdio.h>
#include<assert.h>


struct block_meta{
    int size;
    struct block_meta *next;
    int free;
};
#define META_SIZE sizeof(struct bolck_meta)

void *global = NULL; //header for the linked list
struct block_meta *find_free_block(struct block_meta **last,size_t size){
    struct block_meta* current = global;
    while(current && !(current->free && current->size >= size)){
        *last = current;
        current = current->next;
    }
    return current;
}
struct block_meta * rqst_space(struct block_meta* last, size_t size){
    struct block_meta *block;
    block = sbrk(0);
    void *rqst = sbrk(size+ sizeof(struct block_meta));
    assert((void*)block ==rqst);
    if(rqst==(void*)-1)
        return NULL;
    
    if(last){
        last->next = block;
    }
    block->size = size;
    block->next = NULL;
    block->free = 0;
    return block;
}
void * myMalloc(size_t size){
    struct block_meta *block;
    if(size<=0){
        return NULL;
    }
    if(!global){  //if it's first call
        block = rqst_space(NULL,size);
        if(!block){
            return NULL;
        }
        global = block;  //first 
    }else{
        struct block_meta *last = global;  
        block = find_free_block(&last,size);
        if(!block){
            block = rqst_space(last,size);
            if(!block){
                return NULL;
            }
        }else{
            block->free = 0;
        }
    }
    return (block+1);  //return pointer to next size(+1)
}
struct block_meta *get_block_ptr(void *ptr){
    return (struct block_meta*)ptr -1;
}
void free(void *ptr){
    if(!ptr){
        return ;
    }
    struct block_meta* block_ptr = get_block_ptr(ptr);
    assert(block_ptr->free == 0);
    block_ptr->free = 1;
}
int main(){
    char * p = myMalloc(10);
    if(!p){
        perror("No\n");
    }else{
        printf("yes\n");
    }
    scanf("%s",p);
    printf("%s",p);
    free(p);
    // printf("%d\t%p\n",*p,p);
    // (*p)++;
    // printf("%d\t%p\n",*p,p);
    return 0;
}
