import streamlit as st
from PIL import Image
import math

# ===========================
# 1. Utility Functions
# ===========================

def gaussian_kernel_1d(size, sigma):
    """Generate a 1D Gaussian kernel of given size (odd) and sigma."""
    center = size // 2
    kernel = [0.0] * size
    sum_val = 0.0
    for i in range(size):
        dx = i - center
        val = math.exp(-(dx ** 2) / (2 * sigma ** 2))
        kernel[i] = val
        sum_val += val
    return [v / sum_val for v in kernel]


def apply_convolution_separable(channel, kernel_1d):
    """Apply separable convolution on single-channel image with 1D kernel."""
    h, w = len(channel), len(channel[0])
    pad = len(kernel_1d) // 2
    # horizontal pass
    temp = [[0.0] * w for _ in range(h)]
    for y in range(h):
        for x in range(pad, w - pad):
            acc = 0.0
            for k, val in enumerate(kernel_1d):
                acc += channel[y][x + k - pad] * val
            temp[y][x] = acc
    # vertical pass
    out = [[0.0] * w for _ in range(h)]
    for y in range(pad, h - pad):
        for x in range(w):
            acc = 0.0
            for k, val in enumerate(kernel_1d):
                acc += temp[y + k - pad][x] * val
            out[y][x] = int(min(max(acc, 0), 255))
    return out


def load_image_channels(image: Image.Image):
    """Split PIL image into R,G,B channel matrices."""
    w, h = image.size
    pix = image.load()
    r = [[pix[x, y][0] for x in range(w)] for y in range(h)]
    g = [[pix[x, y][1] for x in range(w)] for y in range(h)]
    b = [[pix[x, y][2] for x in range(w)] for y in range(h)]
    return (r, g, b), w, h


def combine_channels(r, g, b):
    """Combine R,G,B channel matrices into PIL image."""
    h = len(r)
    w = len(r[0])
    img = Image.new("RGB", (w, h))
    for y in range(h):
        for x in range(w):
            img.putpixel((x, y), (
                int(min(max(r[y][x], 0), 255)),
                int(min(max(g[y][x], 0), 255)),
                int(min(max(b[y][x], 0), 255))
            ))
    return img


def subtract(c1, c2):
    """High-pass: subtract blurred channel from original with offset."""
    return [[c1[y][x] - c2[y][x] + 128 for x in range(len(c1[0]))] for y in range(len(c1))]


def add(c1, c2):
    """Combine low-pass and high-pass, reversing offset."""
    return [[min(max(c1[y][x] + c2[y][x] - 128, 0), 255) for x in range(len(c1[0]))] for y in range(len(c1))]

# ===========================
# 2. Hybrid Image Logic
# ===========================

def create_hybrid_image(low_img: Image.Image, high_img: Image.Image, kernel_size: int, sigma: float) -> Image.Image:
    """
    Generate hybrid image by combining low-frequency content of low_img and high-frequency content of high_img.
    """
    # Resize to match
    high_img = high_img.resize(low_img.size)
    # Split channels
    (r1, g1, b1), w, h = load_image_channels(low_img)
    (r2, g2, b2), _, _ = load_image_channels(high_img)
    # Create Gaussian kernel
    kernel_1d = gaussian_kernel_1d(kernel_size, sigma)
    # Low-pass (blur) on base image channels face
    r1b = apply_convolution_separable(r1, kernel_1d)
    g1b = apply_convolution_separable(g1, kernel_1d)
    b1b = apply_convolution_separable(b1, kernel_1d)
    # High-pass detail from second image channels cat
    r2b = apply_convolution_separable(r2, kernel_1d)
    g2b = apply_convolution_separable(g2, kernel_1d)
    b2b = apply_convolution_separable(b2, kernel_1d)
    r2h = subtract(r2, r2b)
    g2h = subtract(g2, g2b)
    b2h = subtract(b2, b2b)
    # Combine channels
    fr = add(r1b, r2h)
    fg = add(g1b, g2h)
    fb = add(b1b, b2h)
    # Convert back to PIL image
    return combine_channels(fr, fg, fb)

# ===========================
# 3. Streamlit App
# ===========================
# from streamlit_custom_notification_box import custom_notification_box
from streamlit_image_comparison import image_comparison
from io import BytesIO

st.set_page_config(page_title="Hybrid Image Generator", layout="wide")


st.markdown("<h1 style='color: #D8BFD8;'>🎭 Hybrid Image Generator</h1>", unsafe_allow_html=True)


# Sidebar controls
st.sidebar.header("Settings")
kernel_size = st.sidebar.slider("Kernel Size", min_value=3, max_value=51, step=2, value=25)
sigma = st.sidebar.slider("Sigma", min_value=0.5, max_value=20.0, step=0.5, value=8.0)


# File upload
low_file = st.sidebar.file_uploader("Low-Frequency Image (e.g. face)", type=["jpg", "jpeg", "png"])
high_file = st.sidebar.file_uploader("High-Frequency Image (e.g. cat)", type=["jpg", "jpeg", "png"])
generate = st.sidebar.button("🔄 Generate Hybrid Image", use_container_width=True)



col_left, col_center, col_right = st.columns([0.5, 2, 0.5])

with col_center:
    col1, col_spacer, col2 = st.columns([1, 0.2, 1])  # 0.2 spacer in between

    if low_file:
        low_img = Image.open(low_file).convert("RGB")
        col1.image(low_img, caption="Low-Frequency Image", use_container_width =True)
    else:
        col1.info("Upload a Low-Frequency Image")

    if high_file:
        high_img = Image.open(high_file).convert("RGB")
        col2.image(high_img, caption="High-Frequency Image", use_container_width=True)
    else:
        col2.info("Upload a High-Frequency Image")





if low_file and high_file and generate:
    with st.spinner('Generating hybrid image...'):
        hybrid = create_hybrid_image(low_img, high_img, kernel_size, sigma)

    st.markdown("<h2 style='color: #E6E6FA;'>Hybrid Output</h2>", unsafe_allow_html=True)
# Centering with columns
    col_left, col_center, col_right = st.columns([1.5, 2, 1])  # Adjust ratios as needed

    with col_center:
        image_comparison(
            img1=hybrid,
            img2=high_img,
            label1="Hybrid Image",
            label2="High-Frequency Image",
            width=500,
            starting_position=50,
            show_labels=True,
            make_responsive=True,
            in_memory=True,
        )

    # st.image(hybrid, use_container_width =True)

    # Convert image to BytesIO in PNG format
    buf = BytesIO()
    hybrid.save(buf, format="PNG")
    buf.seek(0)

    # Download option
    st.download_button("Download Hybrid Image", data=buf, file_name="hybrid.png", mime="image/png")
