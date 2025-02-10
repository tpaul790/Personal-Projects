
/*Shop Products*/
let shop = document.getElementById('shop');

let shopItemData = [{
    id:"1",
    brand:"ZARA",
    price:149.99,
    desc:"Tricou de plaja",
    img:"IMG/products/p1/f1.jpg",
    spr:"p1.html"
},
{
    id:"2",
    brand:"ZARA",
    price:149.99,
    desc:"Tricou de plaja",
    img:"IMG/products/p1/f2.jpg",
    spr:"p2.html"
},
{
    id:"3",
    brand:"ZARA",
    price:149.99,
    desc:"Tricou de plaja",
    img:"IMG/products/p1/f3.jpg",
    spr:"p3.html"
},
{
    id:"4",
    brand:"ZARA",
    price:149.99,
    desc:"Tricou de plaja",
    img:"IMG/products/p1/f4.jpg",
    spr:"p4.html"
},
{
    id:"5",
    brand:"ZARA",
    price:149.99,
    desc:"Tricou de plaja",
    img:"IMG/products/p1/f5.jpg",
    spr:"p5.html"
},
{
    id:"6",
    brand:"MONCLER",
    price:239.99,
    desc:"Cămașă",
    img:"IMG/products/p2/f6.jpg",
    spr:"p6.html"
},
{
    id:"7",
    brand:"ADIDAS",
    price:199.99,
    desc:"Tricou",
    img:"IMG/products/p10/n10.jpg",
    spr:"p7.html"
},
{
    id:"8",
    brand:"BERSHKA",
    price:119.99,
    desc:"Cămașa Evenimente",
    img:"IMG/products/p6/n2.jpg",
    spr:"p8.html"
},
{
    id:"9",
    brand:"BERSHKA",
    price:119.99,
    desc:"Cămașa Evenimente",
    img:"IMG/products/p7/n3.jpg",
    spr:"p9.html"
},
{
    id:"10",
    brand:"BERSHKA",
    price:119.99,
    desc:"Cămașa Evenimente",
    img:"IMG/products/p9/n5.jpg",
    spr:"p10.html"
},
{
    id:"11",
    brand:"BERSHKA",
    price:119.99,
    desc:"Cămașa Evenimente",
    img:"IMG/products/p5/n1.jpg",
    spr:"p11.html"
},
{
    id:"12",
    brand:"PULL&BEAR",
    price:159.99,
    desc:"Cămașă",
    img:"IMG/products/p10/n8.jpg",
    spr:"p12.html"
}
];

let basket = JSON.parse(localStorage.getItem("data")) || [];

let generateShop = () => {
    return shop.innerHTML = shopItemData.map((x) => {
        let {id,brand,price,desc,img,spr} = x;
        let search = basket.find((x) => x.id === id) || [];
        return `
        <div id="product-id-${id}" class="pro">
            <img src="${img}" onclick="window.location.href='${spr}';">
            <div id="productcart" class="des" >
                <span>-${brand}-</span>
                <h5>${desc}</h5>
                <div class="star">
                    <i class="fas fa-star"></i>
                    <i class="fas fa-star"></i>
                    <i class="fas fa-star"></i>
                    <i class="fas fa-star"></i>
                    <i class="fas fa-star"></i>
                </div>
                <h4 id="price">Preț:${price} RON</h4>
                <div class="buttons">
                        <i onclick="decrement(${id})" class="far fa-minus"></i>
                        <div id=${id} class="quantity">${search.item === undefined ? 0: search.item}</div>
                        <i onclick="increment(${id})" class="far fa-plus"></i>
                </div>
            </div>
        </div>
    `
    }).join("");
};

generateShop();

let increment = (id) =>{
    let selectItem = {id};
    let search = basket.find((x)=> x.id === selectItem.id);

    if(search === undefined){
        basket.push({
            id: selectItem.id,
            item: 1,
        });
    }
    else{
        search.item += 1;
    }
    localStorage.setItem("data",JSON.stringify(basket));
    //localStorage.setItem("data",basket);
    update(selectItem.id);   
}

let decrement = (id) =>{
    let selectItem = {id};
    let search = basket.find((x)=> x.id === selectItem.id);

    if(search.item === 0) return;
    else{
        search.item -= 1;
    }
    localStorage.setItem("data",JSON.stringify(basket));
    //localStorage.setItem("data",basket);
    update(selectItem.id);
}

let update = (id) => {
    let search = basket.find((x)=> x.id === id)
    document.getElementById(id).innerHTML = search.item;
    calculation();
};

let calculation = () => {
    let cartIcon = document.getElementById("cartAmount");
    cartIcon.innerHTML = basket.map((x)=>x.item).reduce((x,y)=>x+y,0);
};

calculation();