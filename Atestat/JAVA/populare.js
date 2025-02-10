
/*Populare Products*/
let populare = document.getElementById('populare');

let PopItemData = [{
    id:"7",
    brand:"ADIDAS",
    price:199.99,
    desc:"Tricou",
    img:"IMG/products/p10/n10.jpg",
    spr:"p7.html"
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
    id:"5",
    brand:"ZARA",
    price:149.99,
    desc:"Tricou de plaja",
    img:"IMG/products/p1/f5.jpg",
    spr:"p5.html"
},
{
    id:"11",
    brand:"BERSHKA",
    price:119.99,
    desc:"Cămașa Evenimente",
    img:"IMG/products/p5/n1.jpg",
    spr:"p11.html"
}]

let basket = JSON.parse(localStorage.getItem("data")) || [];

let generatePop = () => {
    return populare.innerHTML = PopItemData.map((x)=>{
        let {id,brand,price,desc,img,spr} = x;
        let search = basket.find((x)=> x.id === id) || [];
        return `
            <div id="product-id-${id}" class="pro">
                <img src="${img}" onclick="window.location.href='${spr}';">
                <div id="productcart" class="des">
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
            </div>`
    }).join("");
};

generatePop();

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
    localStorage.setItem("data", JSON.stringify(basket));
    //console.log(basket);
    update(selectItem.id);
}

let decrement = (id) =>{
    let selectItem = {id};
    let search = basket.find((x)=> x.id === selectItem.id);

    if(search.item === 0) return;
    else{
        search.item -= 1;
    }
    localStorage.setItem("data", JSON.stringify(basket));
    //console.log(basket);
    update(selectItem.id);
}

let update = (id) => {
    let search = basket.find((x)=> x.id === id)
    //console.log(search.item);
    document.getElementById(id).innerHTML = search.item;
    calculation();
};

let calculation = () => {
    let cartIcon = document.getElementById("cartAmount");
    cartIcon.innerHTML = basket.map((x)=>x.item).reduce((x,y)=>x+y,0);
};

calculation();