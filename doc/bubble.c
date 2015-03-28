func bubble_sort(arr) {
    var l = len(arr);
    var beg = 0;
    while(beg < l) {
        var cur = l-1;
        while(cur > beg) {
            if (arr[cur] < arr[cur-1]) {
                var tmp = arr[cur];
                arr[cur] = arr[cur-1];
                arr[cur-1] = tmp;
            }
            cur--;
        }
        beg++;
    }
}

var ls[] = {5,2,5,3,7,1,10};
bubble_sort(ls);
ls;
