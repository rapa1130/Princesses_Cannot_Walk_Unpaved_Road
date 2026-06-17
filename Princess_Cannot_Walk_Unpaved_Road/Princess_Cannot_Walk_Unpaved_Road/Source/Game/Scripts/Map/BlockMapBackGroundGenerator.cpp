#include "BlockMapBackGroundGenerator.h"

#include "Engine/Components/BlockMap/BlockMap.h"

#include "Game/Scripts/Blocks/BlockId.h"

#include <algorithm>

namespace Bisang
{
	namespace
	{
		constexpr int GlyphWidth = 5;
		constexpr int GlyphHeight = 7;
		constexpr int GlyphSpacing = 1;
		constexpr int SpaceWidth = 4;

		const char** GetGlyph(char ch)
		{
			static const char* A[GlyphHeight] = {
				"01110",
				"10001",
				"10001",
				"11111",
				"10001",
				"10001",
				"10001"
			};

			static const char* C[GlyphHeight] = {
				"01111",
				"10000",
				"10000",
				"10000",
				"10000",
				"10000",
				"01111"
			};

			static const char* D[GlyphHeight] = {
				"11110",
				"10001",
				"10001",
				"10001",
				"10001",
				"10001",
				"11110"
			};

			static const char* E[GlyphHeight] = {
				"11111",
				"10000",
				"10000",
				"11110",
				"10000",
				"10000",
				"11111"
			};

			static const char* I[GlyphHeight] = {
				"11111",
				"00100",
				"00100",
				"00100",
				"00100",
				"00100",
				"11111"
			};

			static const char* K[GlyphHeight] = {
				"10001",
				"10010",
				"10100",
				"11000",
				"10100",
				"10010",
				"10001"
			};

			static const char* L[GlyphHeight] = {
				"10000",
				"10000",
				"10000",
				"10000",
				"10000",
				"10000",
				"11111"
			};

			static const char* N[GlyphHeight] = {
				"10001",
				"11001",
				"10101",
				"10011",
				"10001",
				"10001",
				"10001"
			};

			static const char* O[GlyphHeight] = {
				"01110",
				"10001",
				"10001",
				"10001",
				"10001",
				"10001",
				"01110"
			};

			static const char* P[GlyphHeight] = {
				"11110",
				"10001",
				"10001",
				"11110",
				"10000",
				"10000",
				"10000"
			};

			static const char* R[GlyphHeight] = {
				"11110",
				"10001",
				"10001",
				"11110",
				"10100",
				"10010",
				"10001"
			};

			static const char* S[GlyphHeight] = {
				"01111",
				"10000",
				"10000",
				"01110",
				"00001",
				"00001",
				"11110"
			};

			static const char* T[GlyphHeight] = {
				"11111",
				"00100",
				"00100",
				"00100",
				"00100",
				"00100",
				"00100"
			};

			static const char* U[GlyphHeight] = {
				"10001",
				"10001",
				"10001",
				"10001",
				"10001",
				"10001",
				"01110"
			};

			static const char* V[GlyphHeight] = {
				"10001",
				"10001",
				"10001",
				"10001",
				"10001",
				"01010",
				"00100"
			};

			static const char* W[GlyphHeight] = {
				"10001",
				"10001",
				"10001",
				"10101",
				"10101",
				"10101",
				"01010"
			};

			static const char* G[GlyphHeight] = {
				"01111",
				"10000",
				"10000",
				"10011",
				"10001",
				"10001",
				"01111"
			};

			static const char* M[GlyphHeight] = {
				"10001",
				"11011",
				"10101",
				"10101",
				"10001",
				"10001",
				"10001"
			};

			switch (ch)
			{
			case 'A': return A;
			case 'C': return C;
			case 'D': return D;
			case 'E': return E;
			case 'I': return I;
			case 'K': return K;
			case 'L': return L;
			case 'N': return N;
			case 'O': return O;
			case 'P': return P;
			case 'R': return R;
			case 'S': return S;
			case 'T': return T;
			case 'U': return U;
			case 'V': return V;
			case 'W': return W;
			case 'G': return G;
			case 'M': return M;
			default: return nullptr;
			}
		}

		int GetLineWidth(const char* text)
		{
			int width = 0;

			for (int i = 0; text[i] != '\0'; i++)
			{
				if (text[i] == ' ')
					width += SpaceWidth;
				else
					width += GlyphWidth + GlyphSpacing;
			}

			return width > 0 ? width - GlyphSpacing : 0;
		}

		void DrawText(
			BlockMap* map,
			const char* text,
			int canvasX,
			int canvasY,
			int originX,
			int originY,
			int canvasHeight)
		{
			int cursorX = canvasX;

			for (int i = 0; text[i] != '\0'; i++)
			{
				if (text[i] == ' ')
				{
					cursorX += SpaceWidth;
					continue;
				}

				const char** glyph = GetGlyph(text[i]);
				if (glyph == nullptr)
				{
					cursorX += GlyphWidth + GlyphSpacing;
					continue;
				}

				for (int y = 0; y < GlyphHeight; y++)
				{
					for (int x = 0; x < GlyphWidth; x++)
					{
						if (glyph[y][x] == '1')
						{
							int drawX = originX + (canvasHeight - 1 - (canvasY + y));
							int drawY = originY + cursorX + x;



							map->SetBlock(
								{ drawX, drawY, 1 },
								static_cast<int>(BlockId::PinkBlock)
							);
						}
					}
				}

				cursorX += GlyphWidth + GlyphSpacing;
			}
		}
	}

	void BlockMapBackGroundGenerator::GenerateMainBackGround(BlockMap* map)
	{
		if (map == nullptr)
			return;

		const char* lines[] = {
			"PRINCESS",
			"CANNOT WALK",
			"UNPAVED ROAD"
		};

		const int lineCount = 3;
		const int lineGap = 2;
		const int padding = 4;

		int maxLineWidth = 0;
		for (int i = 0; i < lineCount; i++)
		{
			maxLineWidth = (std::max)(maxLineWidth, GetLineWidth(lines[i]));
		}

		const int totalTextHeight =
			lineCount * GlyphHeight + (lineCount - 1) * lineGap;

		const int maxWidth = totalTextHeight + padding * 2;
		const int maxHeight = 2;
		const int maxDepth = maxLineWidth + padding * 2;

		map->InitMap(maxWidth, maxHeight, maxDepth);

		for (int width = 0; width < maxWidth; width++)
		{
			for (int depth = 0; depth < maxDepth; depth++)
			{
				map->SetBlock(
					{ width, depth, 0 },
					static_cast<int>(BlockId::GreenBlock)
				);
			}
		}

		const int originX = padding;
		const int originY = padding;

		for (int i = 0; i < lineCount; i++)
		{
			const int canvasX = 0;
			const int canvasY = i * (GlyphHeight + lineGap);

			DrawText(
				map,
				lines[i],
				canvasX,
				canvasY,
				originX,
				originY,
				totalTextHeight
			);
		}
	}


	void BlockMapBackGroundGenerator::GenerateGameOverBackGround(BlockMap* map)
	{
		if (map == nullptr)
			return;

		const char* lines[] = {
			"GAME",
			"OVER"
		};

		const int lineCount = 2;
		const int lineGap = 2;
		const int padding = 4;

		int maxLineWidth = 0;
		for (int i = 0; i < lineCount; i++)
		{
			maxLineWidth = (std::max)(maxLineWidth, GetLineWidth(lines[i]));
		}

		const int totalTextHeight =
			lineCount * GlyphHeight + (lineCount - 1) * lineGap;

		const int maxWidth = totalTextHeight + padding * 2;
		const int maxHeight = 2;
		const int maxDepth = maxLineWidth + padding * 2;

		map->InitMap(maxWidth, maxHeight, maxDepth);

		for (int width = 0; width < maxWidth; width++)
		{
			for (int depth = 0; depth < maxDepth; depth++)
			{
				map->SetBlock(
					{ width, depth, 0 },
					static_cast<int>(BlockId::YellowBlock)
				);
			}
		}

		const int originX = padding;
		const int originY = padding;

		for (int i = 0; i < lineCount; i++)
		{
			const int canvasX = 0;
			const int canvasY = i * (GlyphHeight + lineGap);

			DrawText(
				map,
				lines[i],
				canvasX,
				canvasY,
				originX,
				originY,
				totalTextHeight
			);
		}
	}

	void BlockMapBackGroundGenerator::GenerateClearBackGround(BlockMap* map)
	{
		if (map == nullptr)
			return;

		const char* lines[] = {
			"CLEAR"
		};

		const int lineCount = 1;
		const int lineGap = 2;
		const int padding = 4;

		int maxLineWidth = 0;
		for (int i = 0; i < lineCount; i++)
		{
			maxLineWidth = (std::max)(maxLineWidth, GetLineWidth(lines[i]));
		}

		const int totalTextHeight =
			lineCount * GlyphHeight + (lineCount - 1) * lineGap;

		const int maxWidth = totalTextHeight + padding * 2;
		const int maxHeight = 2;
		const int maxDepth = maxLineWidth + padding * 2;

		map->InitMap(maxWidth, maxHeight, maxDepth);

		for (int width = 0; width < maxWidth; width++)
		{
			for (int depth = 0; depth < maxDepth; depth++)
			{
				map->SetBlock(
					{ width, depth, 0 },
					static_cast<int>(BlockId::BlueBlock)
				);
			}
		}

		const int originX = padding;
		const int originY = padding;

		for (int i = 0; i < lineCount; i++)
		{
			const int canvasX = 0;
			const int canvasY = i * (GlyphHeight + lineGap);

			DrawText(
				map,
				lines[i],
				canvasX,
				canvasY,
				originX,
				originY,
				totalTextHeight
			);
		}
	}
}