/*
 Copyright (C) 2010-2017 Kristian Duske

 This file is part of TrenchBroom.

 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#include "BrushFaceReader.h"

#include "Model/BrushNode.h"
#include "Model/BrushFace.h"
#include "Model/EntityNode.h"
#include "Model/LayerNode.h"
#include "Model/WorldNode.h"

#include <kdl/vector_utils.h>

#include <string>

namespace TrenchBroom {
    namespace IO {
        BrushFaceReader::BrushFaceReader(const std::string& str, const Model::MapFormat sourceAndTargetMapFormat) :
        MapReader(str, sourceAndTargetMapFormat, sourceAndTargetMapFormat) {}

        std::vector<Model::BrushFace> BrushFaceReader::read(const vm::bbox3& worldBounds, ParserStatus& status) {
            try {
                readBrushFaces(worldBounds, status);
                return std::move(m_brushFaces);
            } catch (const ParserException&) {
                throw;
            }
        }

        Model::Node* BrushFaceReader::onWorldspawn(const std::vector<Model::EntityProperty>& /* attributes */, const ExtraAttributes& /* extraAttributes */, ParserStatus& /* status */) { return nullptr; }
        void BrushFaceReader::onWorldspawnFilePosition(const size_t /* lineNumber */, const size_t /* lineCount */, ParserStatus& /* status */) {}
        void BrushFaceReader::onLayer(Model::LayerNode* /* layer */, ParserStatus& /* status */) {}
        void BrushFaceReader::onNode(Model::Node* /* parent */, Model::Node* /* node */, ParserStatus& /* status */) {}
        void BrushFaceReader::onUnresolvedNode(const ParentInfo& /* parentInfo */, Model::Node* /* node */, ParserStatus& /* status */) {}
        void BrushFaceReader::onBrush(Model::Node* /* parent */, Model::BrushNode* /* brush */, ParserStatus& /* status */) {}

        void BrushFaceReader::onBrushFace(Model::BrushFace face, ParserStatus& /* status */) {
            m_brushFaces.push_back(std::move(face));
        }
    }
}
