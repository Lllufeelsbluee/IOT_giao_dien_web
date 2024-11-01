
// Lấy các nút và hình ảnh bằng id thay vì querySelector
const btnLightOn = document.getElementById('btn1');  
const btnLightOff = document.getElementById('btn2');  
const btnFanOn = document.getElementById('btn3');  
const btnFanOff = document.getElementById('btn4');  
const btnDoorOpen = document.getElementById('btn5');  
const btnDoorClose = document.getElementById('btn6');  

// Lấy hình ảnh theo id mới
const imgLight = document.getElementById('light-img');
const imgFan = document.getElementById('fan-img');
const imgDoor = document.getElementById('door-img');

// Thay đổi hình ảnh cho đèn  
btnLightOn.addEventListener('click', () => {  
    imgLight.src = 'light_on.png'; // Đường dẫn đến hình ảnh đèn bật  
});  

btnLightOff.addEventListener('click', () => {  
    imgLight.src = 'light_off.png'; // Đường dẫn đến hình ảnh đèn tắt  
});  

// Thay đổi hình ảnh cho quạt  
btnFanOn.addEventListener('click', () => {  
    imgFan.src = 'Air_on.png'; // Đường dẫn đến hình ảnh quạt bật  
});  

btnFanOff.addEventListener('click', () => {  
    imgFan.src = 'Air_off.png'; // Đường dẫn đến hình ảnh quạt tắt  
});  

// Thay đổi hình ảnh cho cửa  
btnDoorOpen.addEventListener('click', () => {  
    imgDoor.src = 'open-door.png'; // Đường dẫn đến hình ảnh cửa mở  
});  

btnDoorClose.addEventListener('click', () => {  
    imgDoor.src = 'door.png'; // Đường dẫn đến hình ảnh cửa đóng  
});  


    // Hàm để hiển thị thời gian thực
    function updateClock() {
        const now = new Date();
        
        // Lấy giờ phút giây
        let hours = now.getHours().toString().padStart(2, '0');
        let minutes = now.getMinutes().toString().padStart(2, '0');
        let seconds = now.getSeconds().toString().padStart(2, '0');
        
        // Lấy ngày, tháng, năm
        let day = now.getDate().toString().padStart(2, '0');
        let month = (now.getMonth() + 1).toString().padStart(2, '0'); // Tháng trong JS bắt đầu từ 0
        let year = now.getFullYear();
        
        // Hiển thị giờ
        document.getElementById('clock').textContent = `Time: ${hours}:${minutes}:${seconds}`;
        
        // Hiển thị ngày tháng năm
        document.getElementById('date').textContent = `Date: ${day}/${month}/${year}`;
    }
    
    // Cập nhật đồng hồ mỗi giây
    setInterval(updateClock, 1000);
    
    // Gọi hàm ngay khi trang được tải
    updateClock();
   