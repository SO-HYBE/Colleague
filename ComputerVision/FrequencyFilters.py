import cv2
import numpy as np
import matplotlib.pyplot as plt


def apply_frequency_filters(image_path = r"C:\Users\HYBE\Desktop\HYBE\Projects\Uni-code\ComputerVision\Assets\ss.jpg"):
    img = cv2.imread(image_path, 0)

    if img is None:
        print("Error: Image not found.")
        return

    rows, cols = img.shape
    crow, ccol = rows // 2, cols // 2

    dft = np.fft.fft2(img)
    dft_shift = np.fft.fftshift(dft)

    u = np.arange(rows)
    v = np.arange(cols)
    U, V = np.meshgrid(v, u)
    D = np.sqrt((U - ccol) ** 2 + (V - crow) ** 2)

    D0_low = 30
    ideal_low_pass = np.zeros((rows, cols), dtype=np.float32)
    ideal_low_pass[D <= D0_low] = 1

    D0_high = 30
    n = 2
    butterworth_high_pass = 1 / (1 + (D0_high / (D + 1e-5)) ** (2 * n))

    def reconstruct(shift_spectrum, mask):
        fshift_filtered = shift_spectrum * mask
        f_ishift = np.fft.ifftshift(fshift_filtered)
        img_back = np.fft.ifft2(f_ishift)
        return np.abs(img_back)

    img_low_pass = reconstruct(dft_shift, ideal_low_pass)
    img_high_pass = reconstruct(dft_shift, butterworth_high_pass)

    plt.figure(figsize=(12, 6))

    plt.subplot(131), plt.imshow(img, cmap='gray')
    plt.title('Original Image'), plt.axis('off')

    plt.subplot(132), plt.imshow(img_low_pass, cmap='gray')
    plt.title('Ideal Low Pass'), plt.axis('off')

    plt.subplot(133), plt.imshow(img_high_pass, cmap='gray')
    plt.title('Butterworth High Pass'), plt.axis('off')

    plt.show()

apply_frequency_filters()