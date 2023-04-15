// flatten map into one to one 

const data = [
    { id: 'food', parentId: 'fs' },
    { id: 'threads', parentId: 'fs' },
    { id: 'fs', parentId: 'main' },
    { id: 'food', parentId: 'main' },
    { id: 'main', parentId: null },
    { id: 'fish', parentId: null },
    { id: 'goat', parentId: 'fish' },
];

const idMapping = data.reduce((acc, el, i) => {
    acc[el.id] = i;
    return acc;
}, {});

var maps = {}

let root;
let count = 0;
data.forEach(el => {
    // console.log(el)
    // Handle the root element
    if (el.parentId === null) {
        count++;
        var temp = el.parentId;
        delete el.parentId
        if(maps[count] === undefined )
            maps[count] = el 
        // root = el;
        return;
    }
    // Use our mapping to locate the parent element in our data array
    var idmap = idMapping[el.parentId];
    delete el.parentId;
    const parentEl = data[idmap];
    // console.log(parentEl.parentId)

    //   console.log(parentEl)
    // Add our current el to its parent's `children` array
    parentEl.children = [...(parentEl.children || []), el];
});

console.log(JSON.stringify(maps));

