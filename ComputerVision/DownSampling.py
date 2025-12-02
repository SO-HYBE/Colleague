import cv2
import numpy as np
import matplotlib.pyplot as plt


def apply_antialiasing(image_path, factor=4):
    img = cv2.imread(image_path, 0)

    if img is None:
        print("Error: Image not found.")
        return

    naive_sampling = img[::factor, ::factor]

    k_size = 2 * factor + 1
    img_blurred = cv2.GaussianBlur(img, (k_size, k_size), 0)

    antialiased_sampling = img_blurred[::factor, ::factor]

    plt.figure(figsize=(12, 5))

    plt.subplot(131), plt.imshow(img, cmap='gray')
    plt.title('Original'), plt.axis('off')

    plt.subplot(132), plt.imshow(naive_sampling, cmap='gray')
    plt.title('Naive Sampling (Jagged/Noisy)'), plt.axis('off')

    plt.subplot(133), plt.imshow(antialiased_sampling, cmap='gray')
    plt.title('LPF + Sampling (Smooth)'), plt.axis('off')

    plt.tight_layout()
    plt.show()


apply_antialiasing(r"C:\Users\HYBE\Desktop\HYBE\Projects\Uni-code\ComputerVision\Assets\ss.jpg", factor=4)