
/*Produse Care Urmeaza*/
let urm = document.getElementById('urmeaza');

let UrmItemData = [{
    id:"13",
    brand:"ADIDAS",
    price:99.99,
    desc:"Husă AirPods2",
    img:"IMG/products/p10/n9.jpg",
},
{
    id:"14",
    brand:"ADIDAS",
    price:109.99,
    desc:"Bască",
    img:"IMG/products/p10/n11.jpg",
},
{
    id:"15",
    brand:"ADIDAS",
    price:399.99,
    desc:"Rucsac",
    img:"/IMG/products/p10/n12.jpg",
},
{
    id:"16",
    brand:"PRADA",
    price:599.99,
    desc:"Ochelari de Soare",
    img:"/IMG/products/p10/n13.jpg",
}]

let generateUrm = () => {
    return urm.innerHTML = UrmItemData.map((x)=>{
        let {id,brand,price,desc,img,} = x;
        return `
            <div id="product-id-${id}" class="pro">
                <img src="${img}">
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
                </div>
            </div>`
    }).join("");
};

generateUrm();
