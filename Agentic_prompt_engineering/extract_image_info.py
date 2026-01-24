from PIL import Image
import sys

# Open and display basic info about the images
for img_path in ['SystemPrompt.png', 'UserPrompt.png']:
    print(f"\n{'='*60}")
    print(f"Image: {img_path}")
    print(f"{'='*60}")
    
    img = Image.open(img_path)
    print(f"Size: {img.size}")
    print(f"Mode: {img.mode}")
    
    # Save as high contrast for easier viewing
    # img.show()  # This would open the image viewer
    print(f"\nPlease manually view {img_path} to extract text content")

print("\n" + "="*60)
print("Images are available at:")
print("- SystemPrompt.png")
print("- UserPrompt.png")
print("Please describe their content.")
