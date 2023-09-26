void swap(void *var1, void *var2) {
    void *aux = var1;
    var1 = var2;
    var2 = aux;
}
