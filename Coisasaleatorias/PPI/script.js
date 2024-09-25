// Função para adicionar alerta ao clicar no botão "Adicionar ao Carrinho"
document.querySelectorAll('.add-to-cart').forEach(button => {
    button.addEventListener('click', () => {
        alert('Produto adicionado ao carrinho!');
    });
});

// Função para adicionar um novo card de produto
document.getElementById('add-product').addEventListener('click', () => {
    const productSection = document.getElementById('products');

    const newCard = document.createElement('div');
    newCard.classList.add('card');

    newCard.innerHTML = `
        <h2>Produto X</h2>
        <img src="https://via.placeholder.com/150" alt="Produto X">
        <p>Descrição do Produto X</p>
        <button class="add-to-cart">Adicionar ao Carrinho</button>
    `;

    productSection.appendChild(newCard);

    // Adiciona funcionalidade ao botão do novo card
    newCard.querySelector('.add-to-cart').addEventListener('click', () => {
        alert('Produto adicionado ao carrinho!');
    });
});

// Função para alternar o menu de navegação em dispositivos menores
const menuToggle = document.querySelector('.menu-toggle');
menuToggle.addEventListener('click', () => {
    const menu = document.querySelector('.menu');
    menu.style.display = menu.style.display === 'flex' ? 'none' : 'flex';
});
